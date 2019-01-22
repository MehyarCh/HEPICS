/*
 * NeuralNetwork.cpp
 *
 *  Created on: Jan 17, 2019
 *      Author: Mehyar
 */

#include "NeuralNetwork.h"
#include "Layer.h"
#include "Topology.h"
#include <string>
#include <vector>
#include <iostream>
using namespace std;
class NeuralNetwork{
private:
	string name;
	Topology topology;
	int numberOfLayers;
	vector<Layer> layers;
	static int index;

public:
	NeuralNetwork::NeuralNetwork(string name, int numberOfLayers) {
		this->name=name;
		this->numberOfLayers=numberOfLayers;
		index=0;
	}

	NeuralNetwork::~NeuralNetwork() {
		// TODO Auto-generated destructor stub
	}

	const string& getName() const {
		return name;
	}

	void setName(const string& name) {
		this->name = name;
	}
	void addLayer(Layer layer){
		layers[index]=layer;
		++index;
		if(index==numberOfLayers){
			cout << "All layers are set" << std::endl;
		}
	}

	int getNumberOfLayers() const {
		return numberOfLayers;
	}

	void setNumberOfLayers(int numberOfLayers) {
		this->numberOfLayers = numberOfLayers;
	}

	const Topology& getTopology() const {
		return topology;
	}

	void setTopology(const Topology& topology) {
		this->topology = topology;
	}

	Layer getLayerAt(int i){
		return layers[i];
	}
	void setLayerAt(int i, Layer layer){
		layers[i]=layer;
	}
};

