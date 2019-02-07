/*
 * Image.cpp
 *
 *  Created on: Jan 22, 2019
 *      Author: ibrahim
 */

#include "Image.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Image::Image(int w, int h, int c) {

    this->data = 0;
    this->h = h;
    this->w = w;
    this->c = c;
    this->data = (float *)calloc(h*w*c, sizeof(float));

}

Image::~Image() {
    if(this->data){
        free(this->data);
    };
}

float Image::get_pixel(int x, int y, int c) {
    assert(x < this->w && y < this->h && c < this->c);
    return this->data[c * this->h * this->w + y * this->w + x];
}

void Image::set_pixel(int x, int y, int c, float val)
{
    if (x < 0 || y < 0 || c < 0 || x >= this->w || y >= this->h || c >= this->c) return;
    assert(x < this->w && y < this->h && c < this->c);
    this->data[c * this->h * this->w + y * this->w + x] = val;
}

void Image::add_pixel(int x, int y, int c, float val)
{
    assert(x < this->w && y < this->h && c < this->c);
    this->data[c*this->h*this->w + y*this->w + x] += val;
}

Image Image::load_image_stb(char *filename, int channels) {
    int w, h, c;
    unsigned char *data = stbi_load(filename, &w, &h, &c, channels);
    if (!data) {
        fprintf(stderr, "Cannot load image \"%s\"\nSTB Reason: %s\n", filename, stbi_failure_reason());
        exit(0);
    }
    if(channels) c = channels;
    int i,j,k;
    Image im = Image(w, h, c);
    for(k = 0; k < c; ++k){
        for(j = 0; j < h; ++j){
            for(i = 0; i < w; ++i){
                int dst_index = i + w*j + w*h*k;
                int src_index = k + c*i + c*w*j;
                im.data[dst_index] = (float)data[src_index]/255.;
            }
        }
    }
    free(data);
    return im;
}

void Image::resize_image(int w, int h)
{
    Image part = Image(w, this->h, this->c);
    int r, c, k;
    float w_scale = (float)(this->w - 1) / (w - 1);
    float h_scale = (float)(this->h - 1) / (h - 1);
    for(k = 0; k < this->c; ++k){
        for(r = 0; r < this->h; ++r){
            for(c = 0; c < w; ++c){
                float val = 0;
                if(c == w-1 || this->w == 1){
                    val = get_pixel(this->w-1, r, k);
                } else {
                    float sx = c*w_scale;
                    int ix = (int) sx;
                    float dx = sx - ix;
                    val = (1 - dx) * get_pixel(ix, r, k) + dx * get_pixel(ix+1, r, k);
                }
                part.set_pixel(c, r, k, val);
            }
        }
    }
    for(k = 0; k < this->c; ++k){
        for(r = 0; r < h; ++r){
            float sy = r*h_scale;
            int iy = (int) sy;
            float dy = sy - iy;
            for(c = 0; c < w; ++c){
                float val = (1-dy) * part.get_pixel(c, iy, k);
                set_pixel(c, r, k, val);
            }
            if(r == h-1 || this->h == 1) continue;
            for(c = 0; c < w; ++c){
                float val = dy * part.get_pixel(c, iy+1, k);
                add_pixel(c, r, k, val);
            }
        }
    }

    part.~Image();

}

Image Image::load_image(char *filename, int w, int h, int c) {
    Image out = load_image_stb(filename, c);


    if((h && w) && (h != out.h || w != out.w)){
        out.resize_image(w, h);
    }
    return out;
}

Image Image::load_image_color(char *filename, int w, int h) {
    return load_image(filename, w, h, 3);
}
