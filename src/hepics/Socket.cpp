#include <unistd.h>
#include <sys/socket.h>
#include <netinet/tcp.h>
#include <netdb.h>
#include <cstring>
#include "Socket.h"

namespace hepics {

using namespace std;

Fd::Fd(int fd) :
		fd { fd } {
}

Fd::~Fd() {
	close(fd);
}

static auto make_socket() {
	int s = ::socket(AF_INET, SOCK_STREAM, 0);
	if (s < 0) {
		throw Make_socket_failed { };
	}
	return make_unique<Fd>(s);
}

static auto get_host(const string &hostName) {
	auto host = gethostbyname(hostName.c_str());
	if (host == nullptr) {
		throw Get_host_failed { };
	}
	return host;
}

static auto get_client_addr(const string &hostName, uint16_t port) {
	auto host = get_host(hostName);
	auto addr = sockaddr_in { 0 };
	addr.sin_family = AF_INET;
	memcpy(&addr.sin_addr.s_addr, host->h_addr_list[0], host->h_length);
	addr.sin_port = htons(port);
	return addr;
}

static void connect_client_socket(const Fd &fd, const sockaddr_in &addr) {
	if (connect(fd.fd, reinterpret_cast<const sockaddr*>(&addr), sizeof(addr))
			!= 0) {
		throw Connect_failed { };
	}
}

Socket::Socket(const string &hostName, uint16_t port) :
		fd { make_socket() } {
	auto addr = get_client_addr(hostName, port);
	connect_client_socket(*this->fd, addr);
}

Socket::Socket(unique_ptr<Fd> &&fd) :
		fd { move(fd) } {
}

void Socket::set_tcp_nodelay(bool enabled) const {
	auto value = int { enabled };
	if (setsockopt(fd->fd, IPPROTO_TCP, TCP_NODELAY, &value, sizeof(value))
			!= 0) {
		throw Set_tcp_nodelay_failed { };
	}
}

void Socket::send(const uint8_t *data, size_t length) const {
	if (::send(fd->fd, data, length, 0) < 0) {
		throw Send_failed { };
	}
}

void Socket::receive(uint8_t *data, size_t length) const {
	auto pos = 0;
	auto rem = length;
	while (rem > 0) {
		auto n = recv(fd->fd, &data[pos], rem, 0);
		if (n <= 0) {
			throw Receive_failed { };
		}
		pos += n;
		rem -= n;
	}
}

static auto is_valid_range(const vector<uint8_t> &data, size_t offset,
		size_t length) {
	auto begin = offset;
	auto end = offset + length;
	return begin <= end && end <= data.size();
}

static void ensure_valid_range(const vector<uint8_t> &data, size_t offset,
		size_t length) {
	if (!is_valid_range(data, offset, length)) {
		throw Invalid_range { };
	}
}

void Socket::send(const vector<uint8_t> &data, size_t offset,
		size_t length) const {
	ensure_valid_range(data, offset, length);
	send(&data[offset], length);
}

void Socket::receive(vector<uint8_t> &data, size_t offset,
		size_t length) const {
	ensure_valid_range(data, offset, length);
	receive(&data[offset], length);
}

static auto get_server_addr(uint16_t port) {
	auto addr = sockaddr_in { 0 };
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(port);
	return addr;
}

static void bind_server_socket(const Fd &fd, const sockaddr_in &addr) {
	if (bind(fd.fd, reinterpret_cast<const sockaddr *>(&addr), sizeof(addr))
			!= 0) {
		throw Bind_failed { };
	}
}

static void start_listening(const Fd &fd) {
	if (listen(fd.fd, 1) != 0) {
		throw Listen_failed { };
	}
}

Server_socket::Server_socket(uint16_t port) :
		fd { make_socket() } {
	auto addr = get_server_addr(port);
	bind_server_socket(*fd, addr);
	start_listening(*fd);
}

unique_ptr<Socket> Server_socket::accept() const {
	auto addr = sockaddr_in { 0 };
	auto len = socklen_t { sizeof(addr) };
	auto s = ::accept(fd->fd, reinterpret_cast<sockaddr *>(&addr), &len);
	if (s < 0) {
		throw Accept_failed { };
	}
	return make_unique<Socket>(make_unique<Fd>(s));
}

const char *Socket_exception::what() const noexcept {
	return "socs::socket::SocketException";
}

const char *Make_socket_failed::what() const noexcept {
	return "socs::socket::MakeSocketFailed";
}

const char *Get_host_failed::what() const noexcept {
	return "socs::socket::GetHostFailed";
}

const char *Connect_failed::what() const noexcept {
	return "socs::socket::ConnectFailed";
}

const char *Invalid_range::what() const noexcept {
	return "socs::socket::InvalidRange";
}

const char *Send_failed::what() const noexcept {
	return "socs::socket::SendFailed";
}

const char *Receive_failed::what() const noexcept {
	return "socs::socket::ReceiveFailed";
}

const char *Bind_failed::what() const noexcept {
	return "socs::socket::BindFailed";
}

const char *Listen_failed::what() const noexcept {
	return "socs::socket::ListenFailed";
}

const char *Set_tcp_nodelay_failed::what() const noexcept {
	return "socs::socket::SetTcpNoDelayFailed";
}

const char *Accept_failed::what() const noexcept {
	return "socs::socket::AcceptFailed";
}

} // namespace hepics
