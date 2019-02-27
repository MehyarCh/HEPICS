#include <unistd.h>
#include <fcntl.h>
#include <memory>
#include <climits>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <google/protobuf/text_format.h>

#include "caffe.pb.h"
#include "Caffemodel.h"

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

static void read_message_from_file(Message &message, const string &path) {
	auto file = make_unique<File>(path, O_RDONLY);
	auto fis = make_unique<FileInputStream>(file->fd);
	auto cis = make_unique<CodedInputStream>(fis.get());
	cis->SetTotalBytesLimit(INT_MAX, INT_MAX / 4);
	if (!message.ParseFromCodedStream(cis.get())) {
		throw Parse_failed { };
	}
}

Model::Model(const string &path) {
	auto net_parameter = NetParameter { };
	read_message_from_file(net_parameter, path);
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

} // namespace caffemodel
} // namespace hepics
