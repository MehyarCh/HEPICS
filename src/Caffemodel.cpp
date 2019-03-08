#include <unistd.h>
#include <fcntl.h>
#include <memory>
#include <climits>
#include <unordered_map>
#include <functional>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <google/protobuf/text_format.h>

#include "caffe.pb.h"
#include "Caffemodel.h"

#include "Convolutional_layer.h"
#include "Fully_connected_layer.h"
#include "Maxpool_layer.h"
#include "Function_layer.h"
#include "Local_response_normalization_layer.h"
#include "Image.h"

#include <iostream>

namespace hepics {
namespace caffemodel {

using namespace std;
using google::protobuf::io::FileInputStream;
using google::protobuf::io::CodedInputStream;
using google::protobuf::io::FileOutputStream;
using google::protobuf::TextFormat;
using google::protobuf::Message;
using caffe::NetParameter;
using caffe::FillerParameter;
using caffe::LayerParameter;
using caffe::BlobProto;

struct File {
	File(const string &path, int flags);
	File(const File &file) = delete;
	File(const File &&file) = delete;
	File &operator=(const File &file) = delete;
	File &operator=(const File &&file) = delete;
	~File();

	const int fd;
};

static auto open_file(const string &path, int flags) {
	auto fd = open(path.c_str(), flags, 0644);
	if (fd == -1) {
		throw Open_failed { };
	}
	return fd;
}

File::File(const string &path, int flags) :
		fd { open_file(path, flags) } {
}

File::~File() {
	close(fd);
}

static auto make_image_from_blob(const BlobProto &blob) {
	auto image = make_unique<Image>(blob.width(), blob.height(), blob.channels(), blob.num());
	if (image->size() != size_t(blob.data_size())) {
		throw Invalid_blob_size { };
	}
	auto *a = &image->at(0, 0, 0, 0);
	for (size_t i = 0; i < image->size(); ++i) {
		a[i] = blob.data(i);
	}
	return image;
}

static auto make_vector_from_blob(const BlobProto &blob) {
	auto out = vector<float>();
	for (auto f : blob.data()) {
		out.push_back(f);
	}
	return out;
}

static auto make_layer_factory() {
	auto factory = unordered_map<string, function<unique_ptr<Layer>(const LayerParameter &)>> { };
	factory["Convolution"] = [](const LayerParameter & param) {
		auto filters = make_image_from_blob(param.blobs(0));
		auto bias = make_vector_from_blob(param.blobs(1));
		auto &strides = param.convolution_param().stride();
		auto stride = strides.size() > 0 ? strides.Get(0) : 1;
		auto &pads = param.convolution_param().pad();
		auto pad = pads.size() > 0 ? pads.Get(0) : 0;
		auto groups = param.convolution_param().group();
		return make_unique<Convolutional_layer>(move(filters), move(bias), stride, pad, groups);
	};
	factory["InnerProduct"] = [](const LayerParameter & param) {
		auto weights = make_image_from_blob(param.blobs(0));
		auto bias = make_vector_from_blob(param.blobs(1));
		return make_unique<Fully_connected_layer>(*weights, move(bias));
	};
	factory["LRN"] = [](const LayerParameter & param) {
		return make_unique<Local_response_normalization_layer>();
	};
	factory["Pooling"] = [](const LayerParameter & param) {
		return make_unique<Maxpool_layer>();
	};
	factory["ReLU"] = [](const LayerParameter & param) {
		return make_unique<Relu_layer>();
	};
	factory["SoftmaxWithLoss"] = [](const LayerParameter & param) {
		return make_unique<Softmax_layer>();
	};
	return factory;
}

static auto make_hepics_layer(const LayerParameter &param) {
	static const auto factory = make_layer_factory();
	auto iter = factory.find(param.type());
	if (iter == factory.end()) {
		return unique_ptr<Layer>();
	}
	return iter->second(param);
}

static void read_message_from_file(Message &message, const string &path) {
	auto file = make_unique<File>(path, O_RDONLY);
	auto fis = make_unique<FileInputStream>(file->fd);
	auto cis = make_unique<CodedInputStream>(fis.get());
	cis->SetTotalBytesLimit(INT_MAX, INT_MAX / 4);
	if (!message.ParseFromCodedStream(cis.get())) {
		throw Parse_failed { };
	}
}

vector<unique_ptr<Layer>> Model::parse_layers(const string &path) {
	auto layers = vector<unique_ptr<Layer>>();
	auto net_parameter = NetParameter { };
	read_message_from_file(net_parameter, path);
	for (auto &param : net_parameter.layer()) {
		auto hepics_layer = make_hepics_layer(param);
		if (hepics_layer != nullptr) {
			layers.push_back(move(hepics_layer));
		}
	}
	return layers;
}

void Model::print_short_info(const string &path, ostream &os) {
	auto net_parameter = NetParameter { };
	read_message_from_file(net_parameter, path);
	os << "optional string name = " << net_parameter.name() << "\n";
	os << "repeated LayerParameter layer.size = " << net_parameter.layer_size() << "\n";
	for (int i1 = 0, n1 = net_parameter.layer_size(); i1 < n1; ++i1) {
		auto &layer = net_parameter.layer(i1);
		os << "\n";
		os << "  repeated LayerParameter layer[" << i1 << "] = ...\n";
		os << "    optional string name = " << layer.name() << "\n";
		os << "    optional string type = " << layer.type() << "\n";
		os << "    repeated string bottom.size = " << layer.bottom_size() << "\n";
		for (int i2 = 0, n2 = layer.bottom_size(); i2 < n2; ++i2) {
			os << "      repeated string bottom[" << i2 << "] = " << layer.bottom(i2) << "\n";
		}
		os << "    repeated string top.size = " << layer.top_size() << "\n";
		for (int i2 = 0, n2 = layer.top_size(); i2 < n2; ++i2) {
			os << "      repeated string top[" << i2 << "] = " << layer.top(i2) << "\n";
		}
		os << "    repeated BlobProto blobs.size = " << layer.blobs_size() << "\n";
		for (int i2 = 0, n2 = layer.blobs_size(); i2 < n2; ++i2) {
			auto &blob = layer.blobs(i2);
			os << "      repeated BlobProto blobs[" << i2 << "] = ...\n";
			os << "        repeated float data.size = " << blob.data_size() << "\n";
			os << "        optional int32 num = " << blob.num() << "\n";
			os << "        optional int32 channels = " << blob.channels() << "\n";
			os << "        optional int32 height = " << blob.height() << "\n";
			os << "        optional int32 width = " << blob.width() << "\n";
		}
	}
}

static void write_message_to_json_file(const Message &message, const string &path) {
	auto file = make_unique<File>(path, O_WRONLY | O_CREAT | O_TRUNC);
	auto fos = make_unique<FileOutputStream>(file->fd);
	if (!TextFormat::Print(message, fos.get())) {
		throw Write_text_failed { };
	}
}

static void remove_blobs(NetParameter &net_parameter) {
	auto layer = net_parameter.mutable_layer();
	for (auto &param : *layer) {
		param.clear_blobs();
	}
}

void Model::binary_proto_to_slim_text(const string &in_path, const string &out_path) {
	auto net_parameter = NetParameter { };
	read_message_from_file(net_parameter, in_path);
	remove_blobs(net_parameter);
	write_message_to_json_file(net_parameter, out_path);
}

unique_ptr<Image> Mean::parse_mean(const string &path) {
	auto blob = BlobProto { };
	read_message_from_file(blob, path);
	return make_image_from_blob(blob);
}

void Mean::binary_proto_to_text(const string &in_path, const string &out_path) {
	auto blob = BlobProto { };
	read_message_from_file(blob, in_path);
	write_message_to_json_file(blob, out_path);
}

const char *Model_exception::what() const noexcept {
	return "hepics::Model_exception";
}

const char *Open_failed::what() const noexcept {
	return "hepics::Open_failed";
}

const char *Parse_failed::what() const noexcept {
	return "hepics::Parse_failed";
}

const char *Write_text_failed::what() const noexcept {
	return "hepics::Write_text_failed";
}

const char *Invalid_blob_size::what() const noexcept {
	return "hepics::Invalid_blob_size";
}

} // namespace caffemodel
} // namespace hepics
