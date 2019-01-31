/*
 * Network.h
 *
 *  Created on: Jan 28, 2019
 *      Author: ibrahim
 */

#ifndef NETWORK_H_
#define NETWORK_H_

#include "Image.h"
#include "Convolutional_layer.h"
#include "Connected_layer.h"
#include "Maxpool_layer.h"
#include "Softmax_layer.h"

class Network {
private:
	typedef enum {
		CONVOLUTIONAL,
		CONNECTED,
		MAXPOOL,
		SOFTMAX
	} LAYER_TYPE;

	int n; // number of layers available
	void **layers; // layers will be defined through type casting
	LAYER_TYPE *types;
public:
	Network(int n);
	virtual ~Network();

	void run_network(Image *input, Network net);
	Image get_network_image_layer(Network net);
	
	//getters
	void** getLayers() const;
	int getN() const;
	LAYER_TYPE* Network::getTypes() const {
		return types;
	}

	//setters
	void setLayers(void** layers);
	void setN(int n);
	void setTypes(LAYER_TYPE* types);
};

#endif /* NETWORK_H_ */
