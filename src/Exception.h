#pragma once

#include <exception>

namespace hepics {

class Exception: public std::exception {
public:
	const char *what() const noexcept override;
};

} // namespace hepics
