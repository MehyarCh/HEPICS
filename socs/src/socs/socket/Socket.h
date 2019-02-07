#pragma once

#include <memory>
#include <cstdint>
#include <string>
#include <vector>

#include "../Exception.h"

namespace socs {
namespace socket {

using std::unique_ptr;
using std::string;
using std::vector;
using std::uint8_t;

class Fd {
public:
	Fd(int fd);
	Fd(const Fd &fd) = delete;
	Fd(const Fd &&fd) = delete;
	Fd &operator=(const Fd &fd) = delete;
	Fd &operator=(const Fd &&fd) = delete;
	~Fd();

	const int fd;

};

class Socket {
public:
	Socket(const string &hostName, uint16_t port);
	Socket(unique_ptr<Fd> &&fd);
	void set_tcp_nodelay(bool enabled) const;
	void send(const uint8_t *data, size_t length) const;
	void receive(uint8_t *data, size_t length) const;
	void send(const vector<uint8_t> &data, size_t offset, size_t length) const;
	void receive(vector<uint8_t> &data, size_t offset, size_t length) const;

private:
	const unique_ptr<Fd> fd;

};

class Server_socket {
public:
	Server_socket(uint16_t port);
	unique_ptr<Socket> accept() const;

private:
	unique_ptr<Fd> fd;

};

class Socket_exception: public Exception {
public:
	const char *what() const noexcept override;
};

class Make_socket_failed: public Socket_exception {
public:
	const char *what() const noexcept override;
};

class Get_host_failed: public Socket_exception {
public:
	const char *what() const noexcept override;
};

class Connect_failed: public Socket_exception {
public:
	const char *what() const noexcept override;
};

class Set_tcp_nodelay_failed: public Socket_exception {
public:
	const char *what() const noexcept override;
};

class Invalid_range: public Socket_exception {
public:
	const char *what() const noexcept override;
};

class Send_failed: public Socket_exception {
public:
	const char *what() const noexcept override;
};

class Receive_failed: public Socket_exception {
public:
	const char *what() const noexcept override;
};

class Bind_failed: public Socket_exception {
public:
	const char *what() const noexcept override;
};

class Listen_failed: public Socket_exception {
public:
	const char *what() const noexcept override;
};

class Accept_failed: public Socket_exception {
public:
	const char *what() const noexcept override;
};

} // namespace socket
} // namespace socs
