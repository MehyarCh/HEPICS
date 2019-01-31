/*
 * Image.cpp
 *
 *  Created on: Jan 22, 2019
 *      Author: ibrahim
 */

#include "Image.h"
#include <assert.h> /* assert */

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Image::Image(int h, int w, int c) {
	this->height = h;
	this->width = w;
	this->channels = c;
	this->data = (double*) calloc(height * width * channels, sizeof(double)); // allocate memory for matrix and initialize it with 0 values
}

Image::~Image() {
	if (data) {
		free(data);
	}
}

// Getters
int Image::get_height() {
	return height;
}
int Image::get_width() {
	return width;
}
int Image::get_channels() {
	return channels;
}
double* Image::get_data() {
	return data;
}

// Setters
void Image::set_height(int h) {
	height = h;
}
void Image::set_width(int w) {
	width = w;
}
void Image::set_channels(int c) {
	channels = c;
}
void Image::set_data(double *d) {
	data = d;
}

void Image::zero_image(Image m) {
	memset(m.data, 0, m.height * m.width * m.channels * sizeof(double));
}

void Image::zero_channel(Image m, int c) {
	memset(&(m.data[c * m.height * m.width]), 0, m.height * m.width * sizeof(double));
}

double Image::get_pixel(int x, int y, int c) {
	assert(x < width && y < height && c < channels); /* terminate program execution */
	return data[c * height * width + y * width + x]; // randomly chosen for test
}

double Image::get_pixel_extend(int x, int y, int c) {
	if (c < 0 || c >= channels) return 0;
	return get_pixel(x, y, c);
}

void Image::set_pixel(int x, int y, int c, double val) {
	assert(x < height && y < width && c < channels); /* terminate program execution */
	data[c * height * width + y] = val;
}

void Image::set_pixel_extend(Image m, int x, int y, int c, double val) {
	if ( x <0 || x >= m.height || y < 0 || y > m.width || c < 0 || c >= m.channels) return;
	m.data[c * m.height * m.width + y] = val;
}

void Image::add_pixel(int x, int y, int c, double val) {
	assert(x < height && y < width && c < channels); /* terminate program execution */
	data[c * height * width + y] += val;
}

void Image::add_pixel_extend(int x, int y, int c, double val) {
	if ( x < 0 || x >= height || y < 0 || y > width || c < 0 || c >= channels) return;
	add_pixel(x, y, c, val);
}

void Image::two_d_convolve(int mc, Image *kernel, int kc, int stride, Image out, int oc) {
	int x,y,i,j;
	for (x = 0; x < this->height; x += stride) {
		for (y = 0; y < this->width; y += stride) {
			double sum = 0;
			for (i = 0; i < kernel->height; ++i) {
				for (j = 0; j < kernel->width; ++j) {
					sum += kernel->get_pixel(i, j, kc) * this->get_pixel_extend(x + i - kernel->height / 2, y + j - kernel->width / 2, mc); // Interesting formel, but WHY ?
				}
			}
			out.add_pixel(x / stride, y / stride, oc, sum);
		}
	}
}

void Image::convolve(Image *kernel, int stride, int channel, Image out) {
	assert(this->channels == kernel->channels);
	int i;
	zero_channel(out, channel);
	for (i = 0; i < this->channels; ++i) {
		two_d_convolve(i, kernel, i, stride, out, channel);
	}
}

Image load_image_stb(char *filename, int channels)
{
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

Image Image::resize_image(Image im, int w, int h) {
    Image resized = Image(w, h, im.channels);
    Image part = Image(w, im.height, im.channels);
    int r, c, k;
    float w_scale = (float)(im.width - 1) / (w - 1);
    float h_scale = (float)(im.height - 1) / (h - 1);
    for(k = 0; k < im.channels; ++k){
        for(r = 0; r < im.height; ++r){
            for(c = 0; c < w; ++c){
                float val = 0;
                if(c == w-1 || im.width == 1){
                    val = im.get_pixel(im.width-1, r, k);
                } else {
                    float sx = c*w_scale;
                    int ix = (int) sx;
                    float dx = sx - ix;
                    val = (1 - dx) * im.get_pixel(ix, r, k) + dx * im.get_pixel(ix+1, r, k);
                }
                part.set_pixel(c, r, k, val);
            }
        }
    }
    for(k = 0; k < im.channels; ++k){
        for(r = 0; r < h; ++r){
            float sy = r*h_scale;
            int iy = (int) sy;
            float dy = sy - iy;
            for(c = 0; c < w; ++c){
                float val = (1-dy) * part.get_pixel(c, iy, k);
                resized.set_pixel(c, r, k, val);
            }
            if(r == h-1 || im.height == 1) continue;
            for(c = 0; c < w; ++c){
                float val = dy * part.get_pixel(c, iy+1, k);
                resized.add_pixel(c, r, k, val);
            }
        }
    }

    part.~Image();
    return resized;
}

Image Image::load_image(char *filename, int w, int h, int c) {
    Image out = load_image_stb(filename, c);


    if((h && w) && (h != out.height || w != out.width)){
        Image resized = resize_image(out, w, h);
        out.~Image();
        out = resized;
    }
    return out;
}

Image* Image::make_random_image(int h, int w, int c)
{
    Image *out = new Image(h,w,c);
    int i;
    for(i = 0; i < h*w*c; ++i){
        out->data[i] = (double)rand()/RAND_MAX;
    }
    return out;
}

