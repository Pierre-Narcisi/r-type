/*
** EPITECH PROJECT, 2018
** r-type
** File description:
** FdStream.cpp
*/

#include <cstring>
#include "FdStream.hpp"

namespace common {

std::streambuf::int_type FdStreamBuf::underflow()
{
	if (gptr() < egptr()) // buffer not exhausted
		return traits_type::to_int_type(*gptr());

	char *base = &_buffer.front();
	char *start = base;

	if (eback() == base) // true when this isn't the first fill
	{
		// Make arrangements for putback characters
		std::memmove(base, egptr() - _putBack, _putBack);
		start += _putBack;
	}

	// start is now the start of the buffer, proper.
	// Read from fptr_ in to the provided buffer
	size_t n = std::fread(start, 1, _buffer.size() - (start - base), _fptr);
	if (n == 0)
		return traits_type::eof();

	// Set buffer pointers
	setg(base, start, start + n);

	return traits_type::to_int_type(*gptr());
}

}
