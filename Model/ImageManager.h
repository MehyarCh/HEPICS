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
	QImage* inputImage;
	string inputPath;
public:
	ImageManager(){
		inputImage = new QImage();
	};
	virtual ~ImageManager();
	string getPath();
	void setPath(string path);
	QImage* getImage();
	const QImage* loadInput(const QString path){
		QImage *image = new QImage(path);
			return image;
	};
	QImage convertToRGB(QImage input){
		return input.convertToFormat(QImage::Format_RGBA8888,Qt::AutoColor);
	};

	//needs a test function, converts input to a matrix of pixels
	vector<vector<int>> preProcess(QImage* input){
		vector<vector<int>> matrix;
			for ( int row = 0; row < input->width() -1 ;++row){
				for ( int col = 0; col < input->height() + 1; ++col){
					matrix[row][col]=input->pixelIndex(row,col);
				}
			}
			return matrix;
	};

	//needs a test function, creates a thumbnail
	QImage resize(int length, int width){
		return inputImage->scaled(width, length, Qt::KeepAspectRatio, Qt::FastTransformation);
	};
};

#endif /* MODEL_IMAGEMANAGER_H_ */
