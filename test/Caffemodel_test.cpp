#include <gtest/gtest.h>
#include "../src/Caffemodel.h"

using namespace std;
using namespace hepics::caffemodel;

constexpr auto alexnet_caffemodel_path = "/home/andres/Downloads/bvlc_alexnet.caffemodel";

TEST(caffemodel_test, open) {
	auto model = make_unique<Model>(alexnet_caffemodel_path);
}

TEST(caffemodel_test, open_fails) {
	ASSERT_THROW(make_unique<Model>(""), Open_failed);
}

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

