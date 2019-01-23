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
	Image(int h, int w, int c); // make image
	virtual ~Image(); // free image data

	/* Show image */
	void show_image(Image p, char* name);
	void show_image_layers(Image p, char* name);

	/* Handling image */
	Image make_random_image(int h, int w, int c);
	// Image mahe_random_kernel(int size, int c);
	Image copy_image(Image p);
	Image load_image(char* filename);
	Image get_image_layer(Image m, int l);

	/* Handling pixels */
	double get_pixel(Image m, int x, int y, int c);
	double get_pixel_extend(Image m, int x, int y, int c);
	void set_pixel(Image m, int x, int y, int c, double val);
	void set_pixel_extend(Image m, int x, int y, int c, double val);

	// Convolving
	// void two_d_convolve(Image m, int mc, Image kernel, int kc, int stride, Image out, int oc);

};

#endif /* IMAGE_H_ */
