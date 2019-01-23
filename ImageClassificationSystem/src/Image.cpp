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
	free(data);
}

double Image::get_pixel(Image m, int x, int y, int c) {
	assert(x < m.height && y < m.width && c < m.channels); /* terminate program execution */
	return m.data[c * m.height * m.width + y]; // randomly chosen for test
}

double Image::get_pixel_extend(Image m, int x, int y, int c) {
	if ( x < 0 || x >= m.height || y < 0 || y > m.width || c < 0 || c >= m.channels) return 0;
	return m.data[c * m.height * m.width + y]; // randomly chosen for test
}

void Image::set_pixel(Image m, int x, int y, int c, double val) {
	assert(x < m.height && y < m.width && c < m.channels); /* terminate program execution */
	m.data[c * m.height * m.width + y] = val;
}

void Image::set_pixel_extend(Image m, int x, int y, int c, double val) {
	if ( x <0 || x >= m.height || y < 0 || y > m.width || c < 0 || c >= m.channels) return;
	m.data[c * m.height * m.width + y] = val;
}
