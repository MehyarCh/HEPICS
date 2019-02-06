/*
 * Layer.h
 *
 *  Created on: Jan 31, 2019
 *      Author: ibrahim
 */

#ifndef SRC_LAYER_H_
#define SRC_LAYER_H_

#include <stddef.h>
#include "Tree.h"
#include "Update_args.h"
#include "Layer_Type.h"
#include "Activation.h"
class Network; // forward declaration, avoid circular dependency

class Layer {
public:

	Layer();

	typedef enum{
	    SSE, MASKED, L1, SEG, SMOOTH,WGAN
	} COST_TYPE;

	Layer_Type::LAYER_TYPE type;
	Activation::ACTIVATION activation;
	COST_TYPE cost_type;
	int batch_normalize;
	int shortcut;

	int inputs;
	int outputs;
	int nweights;
	int nbiases;
	int truths;
	int h, w, c;
	int out_h, out_w, out_c;
	int n;
	int max_boxes;
	int size;
	int side;
	int stride;
	int spatial;
	int pad;
	int flip;
	int index;
	int binary;
	int xnor;
	int steps;
	int hidden;
	int truth;
	float smooth;
	float dot;
	float angle;
	float jitter;
	float saturation;
	float exposure;
	float shift;
	float ratio;
	float learning_rate_scale;
	float clip;
	int noloss;
	int softmax;
	int classes;
	int coords;
	int background;
	int rescore;
	int objectness;
	int joint;
	int noadjust;
	int reorg;
	int log;
	int tanh;
	int *mask;
	int total;

	float alpha;
	float beta;
	float kappa;

	float coord_scale;
	float object_scale;
	float noobject_scale;
	float mask_scale;
	float class_scale;
	int bias_match;
	int random;
	float ignore_thresh;
	float truth_thresh;
	float thresh;
	float focus;
	int classfix;
	int absolute;

	int onlyforward;
	int stopbackward;
	int dontload;
	int dontsave;
	int dontloadscales;
	int numload;

	float temperature;
	float probability;
	float scale;

	char * cweights;
	int * indexes;
	int * input_layers;
	int * input_sizes;
	int * map;
	int * counts;
	float ** sums;
	float * rand;
	float * cost;
	float * state;
	float * prev_state;
	float * forgot_state;
	float * forgot_delta;
	float * state_delta;
	float * combine_cpu;
	float * combine_delta_cpu;

	float * concat;
	float * concat_delta;

	float * binary_weights;

	float * biases;
	float * bias_updates;

	float * scales;
	float * scale_updates;

	float * weights;
	float * weight_updates;

	//float * delta;
	float * output;

	float * mean_delta;
	float * variance_delta;

	float * rolling_mean;
	float * rolling_variance;

	float * m;
	float * v;

	float * bias_m;
	float * bias_v;
	float * scale_m;
	float * scale_v;

	float *z_cpu;
	float *r_cpu;
	float *h_cpu;
	float * prev_state_cpu;

	float *temp_cpu;
	float *temp2_cpu;
	float *temp3_cpu;

	float *dh_cpu;
	float *hh_cpu;
	float *prev_cell_cpu;
	float *cell_cpu;
	float *f_cpu;
	float *i_cpu;
	float *g_cpu;
	float *o_cpu;
	float *c_cpu;
	float *dc_cpu;

	float * binary_input;

	struct layer *input_layer;
	struct layer *self_layer;
	struct layer *output_layer;

	struct layer *reset_layer;
	struct layer *update_layer;
	struct layer *state_layer;

	struct layer *input_gate_layer;
	struct layer *state_gate_layer;
	struct layer *input_save_layer;
	struct layer *state_save_layer;
	struct layer *input_state_layer;
	struct layer *state_state_layer;

	struct layer *input_z_layer;
	struct layer *state_z_layer;

	struct layer *input_r_layer;
	struct layer *state_r_layer;

	struct layer *input_h_layer;
	struct layer *state_h_layer;

	struct layer *wz;
	struct layer *uz;
	struct layer *wr;
	struct layer *ur;
	struct layer *wh;
	struct layer *uh;
	struct layer *uo;
	struct layer *wo;
	struct layer *uf;
	struct layer *wf;
	struct layer *ui;
	struct layer *wi;
	struct layer *ug;
	struct layer *wg;

	Tree *softmax_tree;

	size_t workspace_size;
public:

	virtual void forward_layer(Network *net);

	size_t getWorkspaceSize() {
		return workspace_size;
	}

	void setWorkspaceSize(size_t workspaceSize) {
		workspace_size = workspaceSize;
	}

	int getOutC() {
		return out_c;
	}

	void setOutC(int outC) {
		out_c = outC;
	}

	int getOutH() {
		return out_h;
	}

	void setOutH(int outH) {
		out_h = outH;
	}

	int getOutW() {
		return out_w;
	}

	void setOutW(int outW) {
		out_w = outW;
	}

	int getOutputs() {
		return outputs;
	}

	void setOutputs(int outputs) {
		this->outputs = outputs;
	}

	float* getOutput() {
		return output;
	}

	void setOutput(float* output) {
		this->output = output;
	}

	int getN() {
		return n;
	}

	void setN(int n) {
		this->n = n;
	}

	int getSize() {
		return size;
	}

	void setSize(int size) {
		this->size = size;
	}

	int getC() {
		return c;
	}

	void setC(int c) {
		this->c = c;
	}

	int getW() {
		return w;
	}

	void setW(int w) {
		this->w = w;
	}

	int getH() {
		return h;
	}

	void setH(int h) {
		this->h = h;
	}

	float* getCombineDeltaCpu() const {
		return combine_delta_cpu;
	}

	void setCombineDeltaCpu(float* combineDeltaCpu) {
		combine_delta_cpu = combineDeltaCpu;
	}

	float* getConcatDelta() const {
		return concat_delta;
	}

	void setConcatDelta(float* concatDelta) {
		concat_delta = concatDelta;
	}
/*
	float* getDelta() const {
		return delta;
	}

	void setDelta(float* delta) {
		this->delta = delta;
	}
*/
	float* getForgotDelta() {
		return forgot_delta;
	}

	void setForgotDelta(float* forgotDelta) {
		forgot_delta = forgotDelta;
	}

	float* getStateDelta() {
		return state_delta;
	}

	void setStateDelta(float* stateDelta) {
		state_delta = stateDelta;
	}

	Layer_Type::LAYER_TYPE getType() {
		return type;
	}

	void setType(Layer_Type::LAYER_TYPE type) {
		this->type = type;
	}

	Activation::ACTIVATION getActivation() {
		return activation;
	}

	void setActivation(Activation::ACTIVATION activation) {
		this->activation = activation;
	}

	int getNweights() {
		return nweights;
	}

	void setNweights(int nweights) {
		this->nweights = nweights;
	}

	float* getWeights()  {
		return weights;
	}

	void setWeights(float* weights) {
		this->weights = weights;
	}

	static void add_bias(float *output, float *biases, int n, int size);
};

#endif /* SRC_LAYER_H_ */
