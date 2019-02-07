#include "Convolution.h"

namespace socs {
namespace opencl {

using namespace std;

constexpr auto altera_platform_name = "Altera SDK for OpenCL";
constexpr auto de1soc_device_name = "de1soc_sharedonlyCyclone V SoC Development Kit";
constexpr auto cl_path = "/convolution_service/convolution.cl";
constexpr auto aocx_path = "/convolution_service/convolution.aocx";
constexpr auto loop_kernel_name = "loop_main";

Image::Image(uint32_t width, uint32_t height, uint32_t channels, cl_mem_flags flags, const Context &context) :
		width { width }, height { height }, channels { channels },
				data { width * height * channels * sizeof(float), flags, context } {
}

Convolution Convolution::make() {
	auto is_altera = [](const string &name) {return name == altera_platform_name;};
	auto is_de1soc = [](const string &name) {return name == de1soc_device_name;};

	auto platform = Platform { is_altera };
	auto device = Device { is_de1soc, platform };
	auto context = make_shared<Context>(platform, device);
	auto program = is_altera(platform.get_name()) ? make_shared<Program>(aocx_path, *context, device) :
													make_shared<Program>(aocx_path, *context);
	auto loop_kernel = make_shared<Kernel>(*program, loop_kernel_name);
	auto queue = make_shared<Command_queue>(*context, device);

	return Convolution { platform, device, context, program, loop_kernel, queue };
}




}
// namespace opencl
}// namespace socs
