/*
 * ResizeImageN.h
 *
 *  Created on: Feb 15, 2019
 *      Author: bahaa
 */

#ifndef SRC_RESIZEIMAGEN_H_
#define SRC_RESIZEIMAGEN_H_
#include <vector>;
#include <memory>
#include <cstdint>
#include <string>

namespace a {

using std::unique_ptr;
using std::string;
using std::vector;

class ResizeImageN {
public:
	static vector<float> addZeroToChannel(vector<float> &channel, int output,
			int channelLength);
	static vector<float> channelsToVector(vector<float> channel1,
			vector<float> channel2, vector<float> channel3,
			int sizeOfChannelWithZero);
	static vector<float> resizeImage(int w, int h, float *Data, int c, int stride,
			int padding, int filter_length);

	ResizeImageN();
	virtual ~ResizeImageN();
};

} /* namespace a */

#endif /* SRC_RESIZEIMAGEN_H_ */
