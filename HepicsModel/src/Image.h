/*
 * Image.h
 *
 *  Created on: Jan 22, 2019
 *      Author: ibrahim
 */

#ifndef SRC_IMAGE_H_
#define SRC_IMAGE_H_

#include <assert.h>
#include "stb_image.h"
#include "stdlib.h"

class Image {
private:
    int w;
    int h;
    int c;
    float *data;
public:
    static int id;

    Image(int w, int h, int c);
    ~Image();
    float get_pixel(int x, int y, int c);
    void set_pixel(int x, int y, int c, float val);
    void add_pixel(int x, int y, int c, float val);
    void resize_image(int w, int h);
    static Image load_image_stb(char *filename, int channels);
    static Image load_image(char *filename, int w, int h, int c);
    static Image load_image_color(char *filename, int w, int h);

	int getC() {
		return c;
	}

	void setC(int c) {
		this->c = c;
	}

	float* getData() {
		return data;
	}

	void setData(float* data) {
		this->data = data;
	}

	int getH() {
		return h;
	}

	void setH(int h) {
		this->h = h;
	}

	int getW() {
		return w;
	}

	void setW(int w) {
		this->w = w;
	}
	int getId(){
		return id;
	}
};

#endif /* SRC_IMAGE_H_ */
