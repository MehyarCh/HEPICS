/*
 * Image.cpp
 *
 *  Created on: Jan 22, 2019
 *      Author: Mehyar
 */

#include "Image.h"
//#include <QImage>
static int id=0;

Image::Image(int length, int width) {
	// TODO Auto-generated constructor stub
	this->length = length;
	this->width = width;
	id=id+1;
}

Image::~Image() {
	// TODO Auto-generated destructor stub
}

int Image::getLength(){
	return this->length;
}

void Image::setLength(int length) {
	this->length = length;
}

int Image::getWidth(){
	return width;
}

void Image::setWidth(int width) {
	this->width = width;
}

int Image::getId(){
	return id;
}




