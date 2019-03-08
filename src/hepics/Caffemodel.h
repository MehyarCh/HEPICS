#pragma once

#include <string>
#include <ostream>
#include "Exception.h"
#include "Layer.h"

namespace hepics {
namespace caffemodel {

using std::string;
using std::ostream;

class Model {
public:
	static vector<unique_ptr<Layer>> parse_layers(const string &path);

};

struct Mean {
	static unique_ptr<Image> parse_mean(const string &path);
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

class Invalid_blob_size: public Exception {
public:
	const char *what() const noexcept override;
};

} // namespace caffemodel
} // namespace hepics
