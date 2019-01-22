/*
 * Image.cpp
 *
 *  Created on: Jan 22, 2019
 *      Author: Mehyar
 */

#include "Image.h"
#include <QImage>

class Image{
private:
	int length;
	int width;
	static int id=0;
public:
	int getLength() const {
		return length;
	}

	void setLength(int length) {
		this->length = length;
	}

	int getWidth() const {
		return width;
	}

	void setWidth(int width) {
		this->width = width;
	}

	int getId() const {
		return id;
	}

	Image::Image(int length, int width) {
		// TODO Auto-generated constructor stub
		this->length = length;
		this->width = width;
		id=id+1;
	}

	Image::~Image() {
		// TODO Auto-generated destructor stub
	}


};

