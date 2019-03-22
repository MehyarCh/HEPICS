#include <unistd.h>
#include <fcntl.h>
#include <memory>
#include <climits>
#include <unordered_map>
#include <functional>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <google/protobuf/text_format.h>

#include "../proto/caffe.pb.h"
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
		static size_t index = 0;
		auto filters = make_image_from_blob(param.blobs(0));
		auto bias = make_vector_from_blob(param.blobs(1));
		auto &strides = param.convolution_param().stride();
		auto stride = strides.size() > 0 ? strides.Get(0) : 1;
		auto &pads = param.convolution_param().pad();
		auto pad = pads.size() > 0 ? pads.Get(0) : 0;
		auto groups = param.convolution_param().group();
		return make_unique<Convolutional_layer>(move(filters), move(bias), stride, pad, groups, index++);
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

unique_ptr<Image> Mean::parse_mean(const string &path) {
	auto blob = BlobProto { };
	read_message_from_file(blob, path);
	return make_image_from_blob(blob);
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
