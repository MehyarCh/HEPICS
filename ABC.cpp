//============================================================================
// Name        :
// Author      : Bahaa Mahagne
// Version     :
// Copyright   : Your copyright notice
// Description : padding images with 0s to complete size after resizing them to some degree
//============================================================================

#include <iostream>
#include <vector>
#include <cstdint>
#include <cstdint>
#include "Image.h"
#include <memory>
#include <assert.h>
#include <cmath>

using namespace std;

vector<float> addZeroToChannel(vector<float> &channel, int output,
	int channelLength);
vector<float> channelsToVector(vector<float> channel1, vector<float> channel2,

vector<float> channel3, int sizeOfChannelWithZero);

void convertImageToByte(vector<uint8_t> &x, const Image &input)
    {

    int length = (input.getH() * input.getW() * input.getC())
	    * sizeof(input.getData()[0]);

    x.push_back(length);

    const uint8_t* usb = reinterpret_cast<uint8_t*>(input.getData());
    for (int i = 0; i < length; ++i)
	x.push_back(usb[i]);
    }

/**
 * resize the image
 * in = input.
 *
 */
vector<float> resizeImage(const Image &inputImage, int &stride, int &padding,
	int &filter_length)
    {

    int in_length = (inputImage.getW() * inputImage.getH() * inputImage.getC());

    int channelLength = in_length / inputImage.getC();
// 1 mittlere Eintrag
    int output = filter_length - 1 - (2 * padding);

    vector<float> channel1;
    vector<float> channel2;
    vector<float> channel3;

    for (int i = 0; i < in_length; ++i)
	{
	if (i % 3 == 0)
	    {
	    channel1.push_back(inputImage.getData()[i]);
	    }
	if (i % 3 == 1)
	    {
	    channel2.push_back(inputImage.getData()[i]);
	    }
	if (i % 3 == 2)
	    {
	    channel3.push_back(inputImage.getData()[i]);
	    }
	}

    channel1 = addZeroToChannel(channel1, output, channelLength);

    channel2 = addZeroToChannel(channel2, output, channelLength);

    channel3 = addZeroToChannel(channel3, output, channelLength);

    return channelsToVector(channel1, channel2, channel3,
	    channelLength + output);

    }

/**
 * this method returns the channel with zero
 */
vector<float> addZeroToChannel(vector<float> &channel, int output,
	int channelLength)
    {

    int new_length = output + channelLength;
    int newLength2 = ((new_length * new_length) - (2 * new_length));

    vector<float> channelWithZero(new_length);

    for (int i = 0; i < newLength2; (i + output))
	{
	channelWithZero.push_back(0);
	for (int j = 0; j < channelLength; j++)
	    {
	    channelWithZero.push_back(channel[i]);
	    }
	channelWithZero.push_back(0);

	}
    for (int d = 0; d < new_length; d++)
	{
	channelWithZero.push_back(0);
	}

    return channelWithZero;

    }

/**
 * this method returns the Channels as a Vector ({ch1.....ch1ch2......ch2ch3.......ch3})
 */
vector<float> channelsToVector(vector<float> channel1, vector<float> channel2,

vector<float> channel3, int sizeOfChannelWithZero)
    {

    vector<float> outputImage;

    for (int i = 0; i < sizeOfChannelWithZero; i++)
	{
	outputImage.push_back(channel1[i]);

	}
    for (int i = 0; i < sizeOfChannelWithZero; i++)
	{
	outputImage.push_back(channel2[i]);

	}
    for (int i = 0; i < sizeOfChannelWithZero; i++)
	{
	outputImage.push_back(channel3[i]);

	}
    return outputImage;
    }

int main()
    {

    auto image = make_unique<Image>(10, 20, 35);

    vector<float> xy;

    return 0;
    }
