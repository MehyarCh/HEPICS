#if false

void applyFilter(Image &image, Image &filter) {

	int in_h = image.get_height(); //input
	int in_w = image.get_width(); //input
	int out_c; //output
	int in_c = image.get_channels(); //input
	int K_h = filter.get_height(); //filter- number of filters
	int K_w = filter.get_width(); //filter-number of filters
	int out_h; //output
	int out_w; //output
	int S_h; //stride_h
	int S_w; //Stride_w
	int relu_on;
	int N;

	int filter_size_2d = K_h * K_w;
	int filter_size_3d = filter_size_2d * N;

	int ifm_size = in_h * in_w;
	int ofm_size = out_h * out_w;

	for (int row = 0; row < out_h; row++) { // output

		for (int col = 0; col < out_w; col++) { // output

			for (int to = 0; to < out_c; to++) { // output

				for (int ti = 0; ti < in_c; ti++) { // input

					for (int i = 0; i < K_h; i++) { // filter

						for (int j = 0; j < K_w; j++) { //  filter
							int running_sum = running_sum
									+ filter[to * filter_size_3d
											+ ti * filter_size_2d + i * K_w + j]
											* image[ti * ifm_size
													+ (S_h * row + i) * in_w
													+ (S_w * col + j)];
						} // j
					} // i
				} // ti
				int running_sum = running_sum + to;
				if (relu_on)
					int output[to * ofm_size + row * out_w + col] = max(0, running_sum);
				else
					int output[to * ofm_size + row * out_w + col] = running_sum;
				running_sum = 0.0f;
			} // to
		} // col
	} // row
}
}

#endif
