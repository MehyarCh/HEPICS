/*
 * Image.h
 *
 *  Created on: Jan 22, 2019
 *      Author: Mehyar
 */

#ifndef MODEL_IMAGE_H_
#define MODEL_IMAGE_H_

class Image {
private:
	int length;
	int width;
public:
	Image(int length, int width);
	virtual ~Image();
	int getLength();
	void setLength(int length);
	int getWidth();
	void setWidth(int width);
	int getId();
};

#endif /* MODEL_IMAGE_H_ */
