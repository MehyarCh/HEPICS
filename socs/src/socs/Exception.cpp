#include "Exception.h"

namespace socs {

const char *Exception::what() const noexcept {
	return "socs::Exception";
}

} // namespace socs
