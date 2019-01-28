/*
 * Image.cpp
 *
 *  Created on: Jan 22, 2019
 *      Author: ibrahim
 */

#include "Image.h"
#include <assert.h> /* assert */

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

void Image::zero_image(Image m) {
	memset(m.data, 0, m.height * m.width * m.channels * sizeof(double));
}

void Image::zero_channel(Image m, int c) {
	memset(&(m.data[c * m.height * m.width]), 0, m.height * m.width * sizeof(double));
}

double Image::get_pixel(int x, int y, int c) {
	assert(x < height && y < width && c < channels); /* terminate program execution */
	return data[c * height * width + y]; // randomly chosen for test
}

double Image::get_pixel_extend(int x, int y, int c) {
	if ( x < 0 || x >= this->height || y < 0 || y > this->width || c < 0 || c >= this->channels) return 0;
	return this->data[c * this->height * this->width + y]; // randomly chosen for test
}

void Image::set_pixel(int x, int y, int c, double val) {
	assert(x < height && y < width && c < channels); /* terminate program execution */
	data[c * height * width + y] = val;
}

void Image::set_pixel_extend(Image m, int x, int y, int c, double val) {
	if ( x <0 || x >= m.height || y < 0 || y > m.width || c < 0 || c >= m.channels) return;
	m.data[c * m.height * m.width + y] = val;
}

void Image::add_pixel(Image m, int x, int y, int c, double val) {
	assert(x < m.height && y < m.width && c < m.channels); /* terminate program execution */
	m.data[c * m.height * m.width + y] += val;
}

void Image::add_pixel_extend(Image m, int x, int y, int c, double val) {
	if ( x < 0 || x >= m.height || y < 0 || y > m.width || c < 0 || c >= m.channels) return;
	add_pixel(m,x, y, c, val);
}

void Image::two_d_convolve(int mc, Image kernel, int kc, int stride, Image out, int oc) {
	int x,y,i,j;
	for (x = 0; x < this->height; x += stride) {
		for (y = 0; y < this->width; y += stride) {
			double sum = 0;
			for (i = 0; i < kernel.height; ++i) {
				for (j = 0; j < kernel.width; ++j) {
					sum += kernel.get_pixel(i, j, kc) * this->get_pixel_extend(x + i - kernel.height / 2, y + j - kernel.width / 2, mc); // Interesting formel, but WHY ?
				}
			}
			add_pixel(out, x / stride, y / stride, oc, sum);
		}
	}
}

void Image::convolve(Image kernel, int stride, int channel, Image out) {
	assert(this->channels == kernel.channels);
	int i;
	zero_channel(out, channel);
	for (i = 0; i < this->channels; ++i) {
		two_d_convolve(i, kernel, i, stride, out, channel);
	}
}
