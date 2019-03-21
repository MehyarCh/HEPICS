#pragma once

namespace socs {

#if defined(USER_ANDRES)

struct Paths {
	static constexpr auto data_path = "/home/andres/convolutional_layer/";
	static constexpr auto cl_path = "kernel/convolution.cl";
	static constexpr auto aocx_path = "kernel/convolution.aocx";
};

#else

struct Paths {
	static constexpr auto data_path = "/opt/hepics/convolutional_layer/";
	static constexpr auto cl_path = "/opt/hepics/kernel/convolution.cl";
	static constexpr auto aocx_path = "/opt/hepics/kernel/convolution.aocx";
};

#endif

} // namespace socs
