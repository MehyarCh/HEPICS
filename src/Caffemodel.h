#pragma once

#include <string>
#include <ostream>
#include "Exception.h"

namespace hepics {
namespace caffemodel {

using std::string;
using std::ostream;

class Model {
public:
	Model(const string &path);
	Model(const Model &model) = delete;
	Model(const Model &&model) = delete;
	Model &operator=(const Model &model) = delete;
	Model &operator=(const Model &&model) = delete;
	~Model() = default;
	static void print_short_info(const string &path, ostream &os);
	static void binary_proto_to_slim_text(const string &in_path, const string &out_path);

};

class Model_exception: public Exception {
public:
	const char *what() const noexcept override;
};

class Open_failed: public Exception {
public:
	const char *what() const noexcept override;
};

class Parse_failed: public Exception {
public:
	const char *what() const noexcept override;
};

class Write_text_failed: public Exception {
public:
	const char *what() const noexcept override;
};

} // namespace caffemodel
} // namespace hepics
