#include <gtest/gtest.h>
#include "hepics/Caffemodel.h"
#include "Test_paths.h"

using namespace std;
using namespace hepics;
using namespace hepics::caffemodel;


TEST(caffemodel_test, open) {
#ifndef INCLUDE_SLOW_TESTS
	FAIL();
#endif
	if (Test_paths::alexnet_caffemodel == ""s) {
		FAIL();
	}
	auto model = Model::parse_layers(Test_paths::alexnet_caffemodel);
}

TEST(caffemodel_test, open_fails) {
	ASSERT_THROW(Model::parse_layers(""), Open_failed);
}

//TEST(caffemodel_test, convert) {
//	constexpr auto imgnet_mean_bin = "/home/andres/git/caffe/data/ilsvrc12/imagenet_mean.binaryproto";
//	constexpr auto imgnet_mean_txt = "/home/andres/git/caffe/data/ilsvrc12/imagenet_mean.binaryproto.txt";
//	Mean::binary_proto_to_text(imgnet_mean_bin, imgnet_mean_txt);
//}
//
//TEST(caffemodel_test, convert) {
//	constexpr auto alexnet_caffemodel_text_path = "/home/andres/Downloads/bvlc_alexnet.caffemodel.txt";
//	Model::binary_proto_to_slim_text(alexnet_caffemodel_path, alexnet_caffemodel_text_path);
//}
//
//TEST(caffemodel_test, print_short_info_to_cerr) {
//	Model::print_short_info(alexnet_caffemodel_path, cerr);
//}
//
//TEST(caffemodel_test, print_short_info_to_cerr_to_file) {
//	auto fos = make_unique<ofstream>("/home/andres/Downloads/bvlc_alexnet.caffemodel.blob_info");
//	Model::print_short_info(alexnet_caffemodel_path, *fos);
//}

