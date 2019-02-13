/*
 * resize_image_test.cpp
 *
 *  Created on: Feb 11, 2019
 *      Author: bahaa
 */

#include <gtest/gtest.h>
#include <iostream>
#include <vector>
#include <cstdint>
#include <cstdint>
#include <memory>
#include <assert.h>
#include <cmath>
//#include "src/ResizeImage.cpp"
using namespace std;

vector<float> addZeroToChannel2(vector<float> &channel, int output,
		int channelLength);
vector<float> channelsToVector2(vector<float> channel1, vector<float> channel2,

vector<float> channel3, int sizeOfChannelWithZero);

vector<float> resizeImage2(int w, int h, float *D, int c, int stride,
		int padding, int filter_length) {

	int in_length = (w * h * c);

	int channelLength = in_length / c;
// 1 mittleres Eintrag
	int output = filter_length - 1 - (2 * padding);

	vector<float> channel1;
	vector<float> channel2;
	vector<float> channel3;

	for (int i = 0; i < in_length; ++i) {
		if (i % 3 == 0) {
			channel1.push_back(D[i]);
			cout << D[i] << " to 1   ";
		}
		if (i % 3 == 1) {
			channel2.push_back(D[i]);
			cout << D[i] << "to  2    ";
		}
		if (i % 3 == 2) {
			channel3.push_back(D[i]);
			cout << D[i] << " to 3   ";
		}
	}

	vector<float> newchannel1 = addZeroToChannel2(channel1, output,
			channelLength);

	vector<float> newchannel2 = addZeroToChannel2(channel2, output,
			channelLength);

	vector<float> newchannel3 = addZeroToChannel2(channel3, output,
			channelLength);

	return channelsToVector2(newchannel1, newchannel2, newchannel3,
			channelLength + output);

}

/**
 * this method returns the channel with zero
 */
vector<float> addZeroToChannel2(vector<float> &channel, int output,
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

/**
 * this method returns the Channels as a Vector ({ch1.....ch1ch2......ch2ch3.......ch3})
 */
vector<float> channelsToVector2(vector<float> channel1, vector<float> channel2,

vector<float> channel3, int sizeOfChannelWithZero) {

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

vector<float> result;
vector<float> channel01(16);
vector<float> channel02 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
vector<float> channel1 { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

vector<float> channel11 { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };

vector<float> channel2 { 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34,
		35, 36 };
vector<float> channel3 { 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54,
		55, 56 };

TEST(resize_image_test1, test_elements_of_three_channels) { //success
	EXPECT_FALSE(channel1 == channel2);
	EXPECT_FALSE(channel1 == channel3);
	EXPECT_FALSE(channel2 == channel3);
	EXPECT_TRUE(channel01 == channel02);
	//EXPECT_EQ();
}
TEST(resize_image_test2, add_zero_to_channel_length3) { //success: Test for output = 2 und channel length = 3
	vector<float> is = addZeroToChannel2(channel1, 2, 3);
	vector<float> expect { 0, 0, 0, 0, 0, 0, 1, 2, 3, 0, 0, 4, 5, 6, 0, 0, 7, 8,
			9, 0, 0, 0, 0, 0, 0 };

	EXPECT_EQ(expect, is);

}
TEST(resize_image_test3, add_zero_to_channel_length4) { //success: ChannelLength 4
	vector<float> expect { 0, 0, 0, 0, 0, 0, 0, 21, 22, 23, 24, 0, 0, 25, 26,
			27, 28, 0, 0, 29, 30, 31, 32, 0, 0, 33, 34, 35, 36, 0, 0, 0, 0, 0,
			0, 0 };
	vector<float> is = addZeroToChannel2(channel2, 2, 4);

	EXPECT_EQ(expect, is);

}
TEST(resize_image_test4, add_zero_to_channel_length3_output4) { //success

	vector<float> is = addZeroToChannel2(channel1, 4, 3);
	vector<float> expect { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2,
			3, 0, 0, 0, 0, 4, 5, 6, 0, 0, 0, 0, 7, 8, 9, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0 };

	EXPECT_EQ(expect, is);

}

TEST(resize_image_test5, convert_channels_to_vector) { //success

	vector<float> is = channelsToVector2(channel11, channel2, channel3, 4);
	vector<float> expect { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
			16, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36,
			41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56 };

	EXPECT_EQ(expect, is);

}

TEST(resize_image_test6, test_resize_Image) { //failed
	float Data[27] = { 1, 10, 19, 2, 11, 20, 3, 12, 21, 4, 13, 22, 5, 14, 23, 6,
			15, 24, 7, 16, 25, 8, 17, 26, 9, 18, 27 };
	vector<float> is = resizeImage2(3, 3, Data, 3, 1, 1, 3);
	vector<float> expect { 0, 0, 0, 0, 0, 0, 1, 2, 3, 0, 0, 4, 5, 6, 0, 0, 7, 8,
			9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 11, 12, 0, 0, 13, 14, 15,
			0, 0, 16, 17, 18, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 19, 20, 21, 0,
			0, 22, 23, 24, 0, 0, 25, 26, 27, 0, 0, 0, 0, 0, 0 };
	EXPECT_EQ(expect, is);

}

