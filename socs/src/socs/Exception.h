#pragma once

#include <exception>

namespace socs {

class Exception: public std::exception {
public:
	const char *what() const noexcept override;
};

} // namespace socs
