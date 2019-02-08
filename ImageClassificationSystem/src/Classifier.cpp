/*
 * Classifier.cpp
 *
 *  Created on: Feb 3, 2019
 *      Author: ibrahim
 */

#include "Classifier.h"

Classifier::Classifier() {
}

void Classifier::predict_classifier(char *datacfg, char *cfgfile,
		char *weightfile, char *filename, int top) {
	Network *net = Parser::load_network(cfgfile, weightfile);

	List *options = Options_list::read_data_cfg(datacfg);
	char *name_list = Options_list::option_find_str(options, "names", 0);
	int i = 0;
	char **names = Utils::get_labels(name_list);
	clock_t time;
	int *indexes = (int *)calloc(top, sizeof(int));
	char buff[256];
	char *input = buff;

	while (1) {
		if (filename) {
			strncpy(input, filename, 256);
		} else {
			printf("Enter Image Path: ");
			fflush(stdout);
			input = fgets(input, 256, stdin);
			if (!input)
				return;
			strtok(input, "\n");
		}
		Image im = Image::load_image_color(input, 0, 0);
		float *X = im.getData();
		time = clock();
		float *predictions = net->network_predict(X);
		Utils::top_k(predictions, net->getOutputs(), top, indexes);
		fprintf(stderr, "%s: Predicted in %f seconds.\n", input,
				Utils::sec(clock() - time));
		for (i = 0; i < top; ++i) {
			int index = indexes[i];
			printf("%5.2f%%: %s\n", predictions[index] * 100, names[index]);
		}
        //im.~Image();
        if (filename) break;
	}
}

void Classifier::run_classifier(int argc, char **argv) {
	if (argc < 4) {
		fprintf(stderr, "arg is less than four strings");
		return;
	}
	char *data = argv[3]; // "cfg/imagenet1k.data"
	char *cfg = argv[4]; // "cfg/alexnet.cfg"
	char *weights = (argc > 5) ? argv[5] : 0; // "alexnet.weights"
	char *filename = (argc > 6) ? argv[6] : 0; // "data/dog.jpg"
	char *layer_s = (argc > 7) ? argv[7] : 0;
	int layer = layer_s ? atoi(layer_s) : -1; // layer is -1, when layer_s is not given
	int top = TOP;
	predict_classifier(data, cfg, weights, filename, top);
}

