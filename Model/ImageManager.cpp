/*
 * ImageManager.cpp
 *
 *  Created on: Jan 14, 2019
 *      Author: Mehyar
 */

#include "ImageManager.h"
#include "Image.h"
#include <QImage> //still couldn't make it work
#include <string>
#include <vector>
using namespace std;

class ImageManager{
	private :
		Image input;
		string inputPath;

	ImageManager::ImageManager() {
		// TODO Auto-generated constructor stub

	}

	ImageManager::~ImageManager() {
		// TODO Auto-generated destructor stub
	}
	public :
		string getPath(){
			return inputPath;
		}
		void setPath(string path){
			inputPath=path;
		}

		Image getImage(){
			return input;
		}

		Image loadInput(string path){
			//QImage::QImage(fileName, const char* format=nullptr)
			return 0;
		}

		Image convertToRGB(Image input){
			//return input.convertToFormat(QImage::Format_RGBA8888,Qt::AutoColor);
			return 0;
		}


		//needs a test function, converts input to a matrix of pixels

		vector<vector<int>> preProcess(Image input){
			vector<vector<int>> matrix(input.width,input.length);
			/*for ( int row = 0; row < input.width()-1 ; ++row )
			    for ( int col = 0; col < input.height() + 1; ++col )
			    {
			        matrix[row][col]=input.pixelIndex(row,col);*/
			return matrix;
		}

		//needs a test function, creates a thumbnail
		Image resize(int length, int width) {
			//return input.smoothScaled(width, length);
			// QImage::smoothScaled(int w, int h) const
			return 0;
		}

};

