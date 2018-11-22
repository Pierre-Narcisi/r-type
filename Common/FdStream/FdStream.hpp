/*
** EPITECH PROJECT, 2018
** r-type
** File description:
** TcpSocketStream.hpp
*/


#if !defined(_FDSTREAM_HPP)
#define _FDSTREAM_HPP

#include <streambuf>
#include <cstdio>
#include <vector>

#if defined(_MSC_VER)
 #include <io.h>
 #define RTYPE_DUP(fd) _dup(fd)
#else
 #include <unistd.h>
 #define RTYPE_DUP(fd) ::dup(fd)
#endif

namespace common {

class FdStreamBuf: public std::streambuf {
public:
	explicit FdStreamBuf(int fd, std::size_t buffSz = 256, std::size_t putBack = 8):
			_fptr(::fdopen(RTYPE_DUP(fd), "a+")),
			_putBack(std::max(putBack, size_t(1))),
			_buffer(std::max(buffSz, putBack) + putBack) {
		char *end = &_buffer.front() + _buffer.size();
		setg(end, end, end);
	}

	~FdStreamBuf() {
		::fclose(_fptr);
	}

private:
	// overrides base class underflow()
	int_type underflow();

	// copy ctor and assignment not implemented;
	// copying not allowed
	FdStreamBuf(const FdStreamBuf &);
	FdStreamBuf &operator= (const FdStreamBuf &);

private:
	FILE *_fptr;
	const std::size_t _putBack;
	std::vector<char> _buffer;
};

}

#endif // _FDSTREAM_HPP
