#include "App.h"
#include "socket/Socket.h"
#include "opencl/Convolution.h"
#include <memory>
#include <iostream>

#include "make_ptr.h"

namespace socs {

using namespace std;
using namespace opencl;
using namespace socket;

int App::run(int argc, char *argv[]) {
	auto srv_sock = make_unique<Server_socket>(1234);
	auto conv = Convolution::make();
	while (true) {
		auto sock = srv_sock->accept();
		sock->set_tcp_nodelay(true);
		try {
			while (true) {
				size_t param_idx = 0;
				sock->receive(reinterpret_cast<uint8_t *>(&param_idx), sizeof(param_idx));
				size_t width = 0;
				sock->receive(reinterpret_cast<uint8_t *>(&width), sizeof(width));
				size_t height = 0;
				sock->receive(reinterpret_cast<uint8_t *>(&height), sizeof(height));
				size_t channels = 0;
				sock->receive(reinterpret_cast<uint8_t *>(&channels), sizeof(channels));
				auto input = make_unique<Blob>(width, height, channels, 1);
				sock->receive(reinterpret_cast<uint8_t *>(input->ptr()), input->size() * sizeof(*input->ptr()));

				auto output = conv.run(param_idx, *input);
				sock->send(reinterpret_cast<const uint8_t *>(&output->width), sizeof(output->width));
				sock->send(reinterpret_cast<const uint8_t *>(&output->height), sizeof(output->height));
				sock->send(reinterpret_cast<const uint8_t *>(&output->channels), sizeof(output->channels));
				sock->send(reinterpret_cast<const uint8_t *>(output->ptr()), output->size() * sizeof(*output->ptr()));
			}
		} catch (const Exception &e) {
			cerr << e.what() << "\n";
		}
	}
	return 0;
}

int main(int argc, char *argv[]) {
	App app;
	return app.run(argc, argv);
}

} // namespace socs
