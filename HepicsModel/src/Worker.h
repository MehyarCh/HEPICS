/*
 * WorkUnit.h
 *
 *  Created on: Feb 7, 2019
 *      Author: mehyar
 */

#ifndef SRC_WORKER_H_
#define SRC_WORKER_H_

class Worker {
public:
	Worker();
	virtual ~Worker();
	void run_on_cpu();
	void run_on_gpu();
	void run_on_fpga();
};

#endif /* SRC_WORKER_H_ */
