#include "hepics/Network.h"
#include <gtest/gtest.h>
using namespace hepics;

TEST(constructor, test_constructor_network){
#ifndef INCLUDE_SLOW_TESTS
	FAIL();
#endif
	Network* net = new Network();
	ASSERT_EQ(net->get_layers()[0]->get_type(),Layer::Type::convolutional);
	ASSERT_EQ(net->get_layers()[1]->get_type(),Layer::Type::relu);
	ASSERT_EQ(net->get_layers()[2]->get_type(),Layer::Type::local_response_normalization);
	ASSERT_EQ(net->get_layers()[3]->get_type(),Layer::Type::maxpool);
	ASSERT_EQ(net->get_layers()[4]->get_type(),Layer::Type::convolutional);
	ASSERT_EQ(net->get_layers()[5]->get_type(),Layer::Type::relu);
	ASSERT_EQ(net->get_layers()[6]->get_type(),Layer::Type::local_response_normalization);
	ASSERT_EQ(net->get_layers()[7]->get_type(),Layer::Type::maxpool);
	ASSERT_EQ(net->get_layers()[8]->get_type(),Layer::Type::convolutional);

}
