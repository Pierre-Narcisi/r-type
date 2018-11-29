/*
** EPITECH PROJECT, 2018
** r-type
** File description:
** GameProtocol.hpp
*/


#if !defined(_GAMEPROTOCOL_HPP)
#define _GAMEPROTOCOL_HPP

#include <cstdint>
#include "_Network.hpp"

namespace proto {

#if defined(_MSC_VER)  // MSVC
# define DECORATED_STRUCT(name, body) struct name body // Avoid __attibute__
# pragma warning(disable : 4200) //disable an useless warning for all char[] at end of struct
#else // GCC's compilers
# define DECORATED_STRUCT(name, body) struct name body __attribute__((ms_struct)) // use microsoft's struct for file compatibity
#endif


#define PROTO_BASE(_type) \
	Type	type = _type; \
	UInt32	sessionId;

enum class Type: std::uint8_t {
	BASE,
	UDP_RESISTER,
	UDP_CONFIRM,
	MOVE,
	KEYPRESS,
	KEYRELEASE
};

#pragma pack(push, 4) //MSVC compatibility :$

template<typename T, auto toNet, auto toHost>
DECORATED_STRUCT(IntBase, {
	using	ValueType = T;

	IntBase(ValueType	nbr): _nbr(toNet(nbr)) {}

	IntBase		&operator=(ValueType nbr) { _nbr = toNet(nbr); }
	ValueType	operator()() { return toHost(_nbr); }
	void		set(ValueType nbr) { _nbr = toNet(nbr); }
	ValueType	get() { return toHost(_nbr); }
private:
	ValueType	_nbr;
});

using Int16 = IntBase<std::int16_t, htons, ntohs>;
using Int32 = IntBase<std::int32_t, htonl, ntohl>;
using UInt16 = IntBase<std::uint16_t, htons, ntohs>;
using UInt32 = IntBase<std::uint32_t, htonl, ntohl>;

DECORATED_STRUCT(PacketBase, {
	PROTO_BASE(Type::BASE)
private:
	PacketBase() = default;
});

DECORATED_STRUCT(UdpRegister, {
	PROTO_BASE(Type::UDP_RESISTER)

	UInt32	playerId;
});

DECORATED_STRUCT(UdpConfirm, {
	PROTO_BASE(Type::UDP_CONFIRM)

	bool	status;
});

DECORATED_STRUCT(Move, {
	PROTO_BASE(Type::MOVE)

	UInt32	playerId;
	Int32	x;
	Int32	y;
});

DECORATED_STRUCT(KeyPress, {
	PROTO_BASE(Type::KEYPRESS)

	UInt32			playerId;
	std::uint8_t	keyCode;
});

DECORATED_STRUCT(KeyRelease, {
	PROTO_BASE(Type::KEYRELEASE)

	UInt32			playerId;
	std::uint8_t	keyCode;
});

#pragma pack(pop)

#undef PROTO_BASE
#undef DECORATED_STRUCT

} // proto


#endif // _GAMEPROTOCOL_HPP
