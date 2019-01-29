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

class Network {
private:
	typedef enum {
		CONVOLUTIONAL,
		CONNECTED,
		MAXPOOL
	} LAYER_TYPE;

	int n; // number of networks available
	void **layers; // layers will be defined through type casting
	LAYER_TYPE *types;
public:
	Network();
	virtual ~Network();

	void run_network(Image *input, Network net);
	Image get_network_image(Network net);
};

#endif /* NETWORK_H_ */
