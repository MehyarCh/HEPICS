#include <gtest/gtest.h>
#include <cstdint>
#include <vector>
#include <thread>
#include "../../../src/socs/socket/Socket.h"

using namespace std;
using namespace socs::socket;

constexpr auto port = uint16_t { 1234 };

static auto echo(size_t numBytes) {
	auto s = make_unique<Socket>("localhost"s, port);
	s->set_tcp_nodelay(true);
	auto b = vector<uint8_t>(numBytes);
	s->receive(b, 0, b.size());
	s->send(b, 0, b.size());
}

TEST(socket_test, echo_test) {
	auto ss = make_unique<Server_socket>(port);

	auto src = vector<uint8_t> { 123, 21, 12, 32, 1 };
	auto worker = make_unique<thread>(echo, src.size());

	auto s = ss->accept();
	s->set_tcp_nodelay(true);

	s->send(src, 0, src.size());
	auto dst = vector<uint8_t>(src.size());
	s->receive(dst, 0, dst.size());

	worker->join();
	ASSERT_EQ(src, dst);
}
