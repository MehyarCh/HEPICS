/*
 * Image.cpp
 *
 *  Created on: Jan 22, 2019
 *      Author: ibrahim
 */

#include "Image.h"

Image::Image(int h, int w, int c) {
	this->height = h;
	this->width = w;
	this->channels = c;
	this->data = (double*) calloc(height * width * channels, sizeof(double)); // allocate memory for matrix and initialize it with 0 values
}

Image::~Image() {
	free(data);
}

