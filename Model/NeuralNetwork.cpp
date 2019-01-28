/*
 * NeuralNetwork.cpp
 *
 *  Created on: Jan 17, 2019
 *      Author: Mehyar
 */

#include "NeuralNetwork.h"
#include "Layer.h"
#include <QImage>
#include <string>
#include <vector>
#include <iostream>
using namespace std;

NeuralNetwork::NeuralNetwork(string name, int numberOfLayers) {
	this->name=name;
	this->numberOfLayers=numberOfLayers;
	this->index=0;
}

NeuralNetwork::~NeuralNetwork() {
	// TODO Auto-generated destructor stub
}

string NeuralNetwork::getName(){
	return name;
}

void NeuralNetwork::setName(string name) {
	this->name = name;
}

void NeuralNetwork::addLayer(Layer layer){
	layers[index]=layer;
	++index;
	if(index==numberOfLayers){
		cout << "All layers are set" << std::endl;
	}
}

int NeuralNetwork::getNumberOfLayers() {
	return numberOfLayers;
}

void NeuralNetwork::setNumberOfLayers(int numberOfLayers) {
	this->numberOfLayers = numberOfLayers;
}

void NeuralNetwork::displayTopology() {

}

void NeuralNetwork::setTopology(QImage topology) {
	this->topology = topology;
}

QImage NeuralNetwork::getTopology(){
	return this->topology;
}

Layer NeuralNetwork::getLayerAt(int i){
	return layers[i];
}
void NeuralNetwork::setLayerAt(int i, Layer layer){
	layers[i]=layer;
}

