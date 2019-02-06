/*
 * Update_args.h
 *
 *  Created on: Feb 3, 2019
 *      Author: ibrahim
 */

#ifndef SRC_UPDATE_ARGS_H_
#define SRC_UPDATE_ARGS_H_

class Update_args {
private:
    int batch;
    float learning_rate;
    float momentum;
    float decay;
    int adam;
    float B1;
    float B2;
    float eps;
    int t;
public:
	Update_args();
	virtual ~Update_args();

	int getBatch() const {
		return batch;
	}

	void setBatch(int batch) {
		this->batch = batch;
	}
};

#endif /* SRC_UPDATE_ARGS_H_ */
