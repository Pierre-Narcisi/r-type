/*
** EPITECH PROJECT, 2018
** r-type
** File description:
** ATcpSocket.hpp
*/

#if !defined(_ATCP_SOCKET_HPP)
#define _ATCP_SOCKET_HPP

#if defined _MSC_VER
#include <io.h>
using ssize_t = int;
#endif

#include <cstddef>
#include <list>
#include <memory>
#include <cstring>
#include <vector>
#include <mutex>

namespace nw {

class TcpSocket;

class TcpEndpoint {
public:
	TcpEndpoint() = default;
	inline TcpEndpoint(std::string const ip, std::uint16_t port);
	inline TcpEndpoint(int fd, struct sockaddr_in addr);
	~TcpEndpoint() { }
	TcpEndpoint(TcpEndpoint const &) = default;
	TcpEndpoint(TcpEndpoint &&) = default;
	TcpEndpoint &operator=(TcpEndpoint const &) = default;

	inline auto	getResolvedIps() const;

	static inline auto getIp(sockaddr const &addr);

	std::uint16_t	getPort() const { return ntohs(this->_port); }
private:
	std::vector<std::shared_ptr<sockaddr>>	_ai;

	int						_fd;
	std::uint16_t			_port;
	static const int		_family = AF_INET;
	static const int		_socktype = SOCK_STREAM;
	static const int		_protocol = IPPROTO_TCP;

	friend TcpSocket;
};

class ATcpSocket {
public:
	enum class Platform {
		WINDOWS,
		UNIX
	};

	ATcpSocket(Platform p): _platform(p), _init(false) {}
	ATcpSocket(Platform p, TcpEndpoint const &ep):
		_platform(p), _endpoint(ep), _init(true) {}  

	virtual void	connect(const TcpEndpoint &ep) = 0;
	virtual void	write(char const *buffer, std::size_t len) = 0;
	virtual ssize_t	read(char *buffer, std::size_t len) = 0;
	virtual bool	isConnected() = 0;
	virtual void	close() = 0;

	Platform		getPlatfrom(void) { return _platform; }
protected:
	Platform	_platform;
	TcpEndpoint	_endpoint;
	bool		_init;
};

TcpEndpoint::TcpEndpoint(std::string const ip, std::uint16_t port) {
	struct addrinfo	hints;
	struct addrinfo *ai = nullptr;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = _family;
	hints.ai_socktype = _socktype;
	hints.ai_protocol = _protocol;

	int err;
	if ((err = getaddrinfo(ip.c_str(), nullptr, &hints, &ai)) != 0)
		throw std::runtime_error(gai_strerror(err));
	for (auto *cur = ai; cur != nullptr; cur = cur->ai_next) {
		void	*ptr = ::operator new(cur->ai_addrlen);

		std::memmove(ptr, (void*) cur->ai_addr, cur->ai_addrlen);
		_ai.emplace_back(reinterpret_cast<sockaddr*>(ptr));
	}
	freeaddrinfo(ai);
	this->_fd = socket(_family, _socktype, _protocol);
	this->_port = htons(port);
};

TcpEndpoint::TcpEndpoint(int fd, struct sockaddr_in addr):
		_fd(fd) {
	auto &sPtr = _ai.emplace_back(
		reinterpret_cast<sockaddr*>(::operator new(sizeof(addr)))
	);

	std::memmove(sPtr.get(), &addr, sizeof(addr));
}

static std::mutex	getIpLock;
auto	TcpEndpoint::getIp(sockaddr const &addr) {
	static char is[256];
	std::lock_guard<std::mutex> guard(getIpLock);

	getnameinfo(&addr, sizeof(addr), is, sizeof(is), NULL, 0, NI_NUMERICHOST);
	return (std::string(is));
}

auto	TcpEndpoint::getResolvedIps() const {
	std::list<std::string>	res;
	
	for (const auto &cur: _ai) {
		res.push_back(TcpEndpoint::getIp(*cur));
	}
	return res;
}

}

#endif // _ATCP_SOCKET_HPP