/*
 * Image.h
 *
 *  Created on: Jan 22, 2019
 *      Author: ibrahim
 */

#include <stdlib.h>

#ifndef IMAGE_H_
#define IMAGE_H_

class Image {
private:
	int height;
	int width;
	int channels;
	double* data;

public:
	Image(int h, int w, int c);
	virtual ~Image();
	Image load_image(char* filename);
};

#endif /* IMAGE_H_ */
