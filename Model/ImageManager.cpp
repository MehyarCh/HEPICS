/*
 * ImageManager.cpp
 *
 *  Created on: Jan 14, 2019
 *      Author: Mehyar
 */

#include "ImageManager.h"
#include "Image.h"
#include <QImage>
#include <string>
#include <vector>
#include <QString>

using namespace std;

ImageManager::ImageManager() {
	// TODO Auto-generated constructor stub
}

ImageManager::~ImageManager() {
	// TODO Auto-generated destructor stub
}
string ImageManager::getPath(){
	return inputPath;
}
void ImageManager::setPath(string path){
	inputPath=path;
}

QImage ImageManager::getImage(){
	return inputImage;
}

QImage ImageManager::loadInput(QString path){
	QImage image = QImage(path);
	return image;
}

QImage ImageManager::convertToRGB(QImage input){
	return input.convertToFormat(QImage::Format_RGBA8888,Qt::AutoColor);
}


//needs a test function, converts input to a matrix of pixels
vector<vector<int>> ImageManager::preProcess(QImage input){
	vector<vector<int>> matrix;
	for ( int row = 0; row < input.width()-1 ; ++row ){
		for ( int col = 0; col < input.height() + 1; ++col ){
			matrix[row][col]=input.pixelIndex(row,col);
		}
	}
	return matrix;
}

//needs a test function, creates a thumbnail
QImage ImageManager::resize(int length, int width) {
	/*scaled(int width, int height, Qt AspectRatioMode, Qt Transformation mode)
	AspectRatioMode :
		0: size is scaled freely, aspect ratio not preserved
		1: preserve the aspect ratio (probably what we want)
	TransformationMode:
		0: quick, no smoothing
		1: bilinear filtering
	*/
	return inputImage.scaled(width, length, Qt::KeepAspectRatio, Qt::FastTransformation);
}


