/*
 * NeuralNetwork.h
 *
 *  Created on: Jan 17, 2019
 *      Author: Mehyar
 */

#ifndef NEURALNETWORK_H_
#define NEURALNETWORK_H_

#include <QImage>
#include "Layer.h"
#include <string>
#include <vector>
#include <iostream>
using namespace std;

class NeuralNetwork {
private:
	string name;
	QImage *topology;
	int numberOfLayers;
	vector<Layer> layers;
	int *index;
public:
	NeuralNetwork(string name, int numberOfLayers);
	string getName();
	void setName(string name);
	void addLayer(Layer layer);
	int getNumberOfLayers();
	void setNumberOfLayers(int numberOfLayers);
	void displayTopology();
	void setTopology(QImage* topology);
	QImage* getTopology();
	Layer getLayerAt(int i);
	void setLayerAt(int i, Layer layer);
};

#endif /* NEURALNETWORK_H_ */
