#include "Exception.h"

namespace hepics {

const char *Exception::what() const noexcept {
	return "socs::Exception";
}

} // namespace hepics
