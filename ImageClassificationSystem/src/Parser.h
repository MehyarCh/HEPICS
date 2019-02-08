/*
 * Parser.h
 *
 *  Created on: Feb 2, 2019
 *      Author: ibrahim
 */

#ifndef SRC_PARSER_H_
#define SRC_PARSER_H_

#include <stdio.h>
#include "Network.h"
#include "List.h"
#include "Section.h"
#include "Options_list.h"
#include "Utils.h"
#include "Layer.h"
#include "Activation.h"
#include "Convolutional_layer.h"
#include "Maxpool_layer.h"
#include "Connected_layer.h"
#include "Softmax_layer.h"

class Parser {
private:
	typedef struct size_params {
		int batch;
		int inputs;
		int h;
		int w;
		int c;
		int index;
		int time_steps;
		Network *net;
	} size_params;
public:

	static List *read_cfg(char *filename) {
		FILE *file = fopen(filename, "r");
		if (file == 0)
			Utils::file_error(filename);
		char *line;
		int line_num = 0;
		List *options = new List();
		Section *current = 0;

		while ((line = Utils::fgetl(file)) != 0) {
			++line_num;
			Utils::strip(line);
			switch (line[0]) {
			case '[':
				current = new Section();
				options->list_insert(current);
				current->setOptions(new List());
				current->setType(line);
				break;
			case '\0':
			case '#':
			case ';':
				free(line);
				break;
			default:
				if (!Options_list::read_option(line, current->getOptions())) {
					fprintf(stderr,
							"Config file error line %d, could parse: %s\n",
							line_num, line);
					free(line);
				}
				break;
			}
		}
		fclose(file);
		return options;
	}

	static int is_network(Section *s) {
		return (strcmp(s->getType(), "[net]") == 0
				|| strcmp(s->getType(), "[network]") == 0);
	}

	static void parse_net_options(List *options, Network *net) {
		net->setBatch(Options_list::option_find_int(options, "batch", 1));

		net->setH(Options_list::option_find_int_quiet(options, "height", 0));
		net->setW(Options_list::option_find_int_quiet(options, "width", 0));
		net->setC(Options_list::option_find_int_quiet(options, "channels", 0));
		net->setInputs(
				Options_list::option_find_int_quiet(options, "inputs",
						net->getH() * net->getW() * net->getC()));
		if (!net->getInputs() && !(net->getH() && net->getW() && net->getC()))
			Utils::error("No input parameters supplied");
	}

	static void free_section(Section *s) {
		free(s->getType());
		Node *n = s->getOptions()->getFront();
		while (n) {
			Options_list *pair = (Options_list *) n->getVal();
			free(pair->getKey());
			free(pair);
			Node *next = n->getNext();
			free(n);
			n = next;
		}
		free(s->getOptions());
		free(s);
	}

	static Convolutional_layer parse_convolutional(List *options,
			size_params params) {
		int n = Options_list::option_find_int(options, "filters", 1);
		int size = Options_list::option_find_int(options, "size", 1);
		int stride = Options_list::option_find_int(options, "stride", 1);
		int pad = Options_list::option_find_int_quiet(options, "pad", 0);
		int padding = Options_list::option_find_int_quiet(options, "padding",
				0);
		int groups = Options_list::option_find_int_quiet(options, "groups", 1);
		if (pad)
			padding = size / 2;

		char *activation_s = Options_list::option_find_str(options,
				"activation", "logistic");
		Activation act = Activation(activation_s);
		Activation::ACTIVATION activation = act.get_activation();

		int batch, h, w, c;
		h = params.h;
		w = params.w;
		c = params.c;
		batch = params.batch;
		if (!(h && w && c))
			Utils::error("Layer before convolutional layer must output image.");

		Convolutional_layer layer = Convolutional_layer(h, w, c, n, size, stride, padding, activation);

		return layer;
	}

	static Maxpool_layer parse_maxpool(List *options, size_params params) {
		int stride = Options_list::option_find_int(options, "stride", 1);
		int size = Options_list::option_find_int(options, "size", stride);
		int padding = Options_list::option_find_int_quiet(options, "padding",
				size - 1);

		int batch, h, w, c;
		h = params.h;
		w = params.w;
		c = params.c;
		batch = params.batch;
		if (!(h && w && c))
			Utils::error("Layer before maxpool layer must output image.");

		Maxpool_layer layer = Maxpool_layer(batch, h, w, c, size, stride,
				padding);
		return layer;
	}

	static Connected_layer parse_connected(List *options, size_params params) {
		int output = Options_list::option_find_int(options, "output", 1);
		char *activation_s = Options_list::option_find_str(options,
				"activation", "logistic");
		Activation act = Activation(activation_s);
		Activation::ACTIVATION activation = act.get_activation();
		int batch_normalize = Options_list::option_find_int_quiet(options,
				"batch_normalize", 0);

		Connected_layer l = Connected_layer(params.inputs, output, activation);
		return l;
	}

	static Softmax_layer parse_softmax(List *options, size_params params)
	{
	    int groups = Options_list::option_find_int_quiet(options, "groups",1);
	    Softmax_layer l = Softmax_layer(params.inputs);
	    l.setW(params.w);
	    l.setH(params.h);
	    l.setC(params.c);
	    return l;
	}

	static Layer_Type::LAYER_TYPE string_to_layer_type(char * type) {
		if (strcmp(type, "[conv]") == 0 || strcmp(type, "[convolutional]") == 0)
			return Layer_Type::CONVOLUTIONAL;
		if (strcmp(type, "[max]") == 0 || strcmp(type, "[maxpool]") == 0)
			return Layer_Type::MAXPOOL;
		if (strcmp(type, "[conn]") == 0 || strcmp(type, "[connected]") == 0)
			return Layer_Type::CONNECTED;
	    if (strcmp(type, "[soft]")==0
	            || strcmp(type, "[softmax]")==0) return Layer_Type::SOFTMAX;
	}

	static Network *parse_network_cfg(char *filename) {
		List *sections = read_cfg(filename);
		Node *n = sections->getFront();
		if (!n)
			Utils::error("Config file has no sections");
		Network *net = Network::make_network(sections->getSize() - 1);
		size_params params;

		Section *s = (Section *) n->getVal();
		List *options = s->getOptions();
		if (!is_network(s))
			Utils::error("First section must be [net] or [network]");
		parse_net_options(options, net);

		params.h = net->getH();
		params.w = net->getW();
		params.c = net->getC();
		params.inputs = net->getInputs();
		params.batch = net->getBatch();
		params.net = net;

		size_t workspace_size = 0;
		n = n->getNext();
		int count = 0;
		free_section(s);
		fprintf(stderr,
				"layer     filters    size              input                output\n");
		while (n) {
			params.index = count;
			fprintf(stderr, "%5d ", count);
			s = (Section *) n->getVal();
			options = s->getOptions();
			Layer l = Layer(); // empty layer
			Layer_Type::LAYER_TYPE lt = string_to_layer_type(s->getType());

			if (lt == Layer_Type::CONVOLUTIONAL) {
				l = parse_convolutional(options, params);
			} else if (lt == Layer_Type::MAXPOOL) {
				l = parse_maxpool(options, params);
			} else if (lt == Layer_Type::CONNECTED) {
				l = parse_connected(options, params);
			} else if (lt == Layer_Type::SOFTMAX) {
				l = parse_softmax(options, params);
			} else {
				fprintf(stderr, "Type not recognized: %s\n", s->getType());
			}

			net->layers[count] = l;
			net->layers->type = l.type;
			if (l.getWorkspaceSize() > workspace_size)
				workspace_size = l.getWorkspaceSize();
			free_section(s);
			n = n->getNext();
			++count;
			if (n) {
				params.h = l.getOutH();
				params.w = l.getOutW();
				params.c = l.getOutC();
				params.inputs = l.getOutputs();
			}
		}
		sections->~List();
		Layer out = net->get_network_output_layer();
		net->setOutputs(out.getOutputs());
		net->setOutput(out.getOutput());
		net->setInput(
				(float *) calloc(net->getInputs() * net->getBatch(),
						sizeof(float)));
		 net->workspace = (float *)calloc(1, workspace_size);
		 //net->layers = net->layers - count - 1;
		return net;
	}

	static Network *load_network(char *cfg, char *weights) {
		Network *net = parse_network_cfg(cfg);
		return net;
	}

};

#endif /* SRC_PARSER_H_ */
