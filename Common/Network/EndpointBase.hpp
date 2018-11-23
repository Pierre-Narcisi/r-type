/*
** EPITECH PROJECT, 2018
** r-type
** File description:
** EndpointBase.hpp
*/


#if !defined(_ENDPOINTBASE_HPP)
#define _ENDPOINTBASE_HPP

#include "_Network.hpp"

#include <cstddef>
#include <list>
#include <memory>
#include <cstring>
#include <vector>
#include <mutex>

namespace nw {

class EndpointBase {
public:
	EndpointBase(int f, int s, int p):
		_family(f), _socktype(s), _protocol(p) {}
	~EndpointBase() { }
	EndpointBase(EndpointBase const &) = default;
	EndpointBase(EndpointBase &&) = default;
	EndpointBase &operator=(EndpointBase const &) = default;

	inline auto	getResolvedIps() const;

	static inline auto getIp(sockaddr const &addr);

	std::uint16_t	getPort() const { return ntohs(this->_port); }
protected:
	inline void	_fromIpPort(std::string const ip, std::uint16_t port);
	inline void	_fromAddr(struct sockaddr_in addr);

	std::vector<std::shared_ptr<sockaddr>>	_ai;

	std::uint16_t	_port;
	int				_family;
	int				_socktype;
	int				_protocol;
};

void	EndpointBase::_fromIpPort(std::string const ip, std::uint16_t port) {
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
	this->_port = htons(port);
};

void	EndpointBase::_fromAddr(struct sockaddr_in addr) {
	auto &sPtr = _ai.emplace_back(
		reinterpret_cast<sockaddr*>(::operator new(sizeof(addr))));

	std::memmove(sPtr.get(), &addr, sizeof(addr));
}

static std::mutex	getIpLock;
auto	EndpointBase::getIp(sockaddr const &addr) {
	static char is[256];
	std::lock_guard<std::mutex> guard(getIpLock);

	getnameinfo(&addr, sizeof(addr), is, sizeof(is), NULL, 0, NI_NUMERICHOST);
	return (std::string(is));
}

auto	EndpointBase::getResolvedIps() const {
	std::list<std::string>	res;
	
	for (const auto &cur: _ai) {
		res.push_back(EndpointBase::getIp(*cur));
	}
	return res;
}

}

#endif // _ENDPOINTBASE_HPP
