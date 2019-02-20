/*
 * Layer_Type.h
 *
 *  Created on: Feb 3, 2019
 *      Author: ibrahim
 */

#ifndef LAYER_TYPE_H_
#define LAYER_TYPE_H_

class Layer_Type {
public:
	typedef enum {
	    CONVOLUTIONAL,
	    CONNECTED,
	    MAXPOOL,
	    SOFTMAX,
	    DROPOUT,
	    AVGPOOL,
	} LAYER_TYPE;
};

#endif /* LAYER_TYPE_H_ */
