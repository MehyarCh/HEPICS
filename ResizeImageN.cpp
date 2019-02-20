/*
 * ResizeImageN.cpp
 *
 *  Created on: Feb 15, 2019
 *      Author: bahaa
 */

#include "ResizeImageN.h"

namespace a {

vector<float> ResizeImageN::resizeImage(int w, int h, float *Data, int c,
		int stride, int padding, int filter_length) {

	int in_length = (w * h * c);

	int channelLength = in_length / c;
	// 1 mittleres Eintrag
	int output = filter_length - 1 - (2 * padding);

	vector<float> channel1;
	vector<float> channel2;
	vector<float> channel3;

	for (int i = 0; i < in_length; ++i) {
		if (i % 3 == 0) {
			channel1.push_back(Data[i]);
		}
		if (i % 3 == 1) {
			channel2.push_back(Data[i]);
		}
		if (i % 3 == 2) {
			channel3.push_back(Data[i]);
		}
	}

	vector<float> newchannel1 = addZeroToChannel(channel1, output, w);

	vector<float> newchannel2 = addZeroToChannel(channel2, output, w);

	vector<float> newchannel3 = addZeroToChannel(channel3, output, w);

	return channelsToVector(newchannel1, newchannel2, newchannel3, w + output);

}

vector<float> ResizeImageN::addZeroToChannel(vector<float> &channel, int output,
		int channelLength) {

	int new_length = output + channelLength;
	int reply = output / 2;
	vector<float> channelWithZero(reply * new_length);
	int d = 0;
	for (int i = 0; i < channelLength; i++) {
		for (int i = 0; i < reply; i++)
			channelWithZero.push_back(0);
		for (int j = 0; j < channelLength; j++) {
			channelWithZero.push_back(channel[d]);
			d++;
		}
		for (int i = 0; i < reply; i++)
			channelWithZero.push_back(0);

	}
	for (int d = 0; d < (reply * new_length); d++) {
		channelWithZero.push_back(0);
	}

	return channelWithZero;
}

vector<float> ResizeImageN::channelsToVector(vector<float> channel1,
		vector<float> channel2, vector<float> channel3,
		int sizeOfChannelWithZero) {

	vector<float> outputImage;
	int length = (sizeOfChannelWithZero * sizeOfChannelWithZero);

	for (int i = 0; i < length; i++) {
		outputImage.push_back(channel1[i]);

	}
	for (int i = 0; i < length; i++) {
		outputImage.push_back(channel2[i]);

	}
	for (int i = 0; i < length; i++) {
		outputImage.push_back(channel3[i]);

	}
	return outputImage;

}

ResizeImageN::ResizeImageN() {
	// TODO Auto-generated constructor stub

}

ResizeImageN::~ResizeImageN() {
	// TODO Auto-generated destructor stub
}

} /* namespace a */
