/*
 * ImageManager.h
 *
 *  Created on: Jan 14, 2019
 *      Author: Mehyar
 */

#ifndef MODEL_IMAGEMANAGER_H_
#define MODEL_IMAGEMANAGER_H_
#include <string>
#include "Image.h"
#include <QImage>
#include <QString>
using namespace std;

class ImageManager {
private :
	QImage inputImage;
	string inputPath;
public:
	ImageManager();
	virtual ~ImageManager();
	string getPath();
	void setPath(string path);
	QImage getImage();
	QImage loadInput(QString path);
	QImage convertToRGB(QImage input);

	//needs a test function, converts input to a matrix of pixels
	vector<vector<int>> preProcess(QImage input);

	//needs a test function, creates a thumbnail
	QImage resize(int length, int width);
};

#endif /* MODEL_IMAGEMANAGER_H_ */
