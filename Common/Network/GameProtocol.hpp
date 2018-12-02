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
	UInt32	sessionId; \
	UInt32	playerId;

enum class Type: std::uint8_t {
	BASE,
	PING,
	UDP_REGISTER,
	UDP_CONFIRM,
	CREATE,
	DELETE,
	MOVE,
	KEYPRESS,
	KEYRELEASE
};

enum class SpriteId: std::uint8_t {
	PLAYER1, //"assets/Sprite/Ship/BlueShip/BlueShip3.png"
	PLAYER2, //"assets/Sprite/Ship/GreenShip/GreenShip3.png"
	PLAYER3, //"assets/Sprite/Ship/PurpleShip/PurpleShip3.png"
	PLAYER4, //"assets/Sprite/Ship/RedShip/RedShip3.png"

	BACKGROUND, //"assets/space.png"

	WALL1, //"assets/Sprite/Walls/Wall1.png"
	WALL2, //"assets/Sprite/Walls/Wall2.png"
	WALL3, //"assets/Sprite/Walls/Wall3.png"
	WALL4, //"assets/Sprite/Walls/Wall4.png"
	WALL5, //"assets/Sprite/Walls/Wall5.png"
	WALL6, //"assets/Sprite/Walls/Wall6.png"
	WALL7, //"assets/Sprite/Walls/Wall7.png"
	WALL8, //"assets/Sprite/Walls/Wall8.png"
	WALL_ROTATE1, //"assets/Sprite/WallsRotate/Wall1.png"
	WALL_ROTATE2, //"assets/Sprite/WallsRotate/Wall2.png"
	WALL_ROTATE3, //"assets/Sprite/WallsRotate/Wall3.png"
	WALL_ROTATE4, //"assets/Sprite/WallsRotate/Wall4.png"
	WALL_ROTATE5, //"assets/Sprite/WallsRotate/Wall5.png"
	WALL_ROTATE6, //"assets/Sprite/WallsRotate/Wall6.png"
	WALL_ROTATE7, //"assets/Sprite/WallsRotate/Wall7.png"
	WALL_ROTATE8, //"assets/Sprite/WallsRotate/Wall8.png"

	BONUS, //"assets/Sprite/Bonuses/bonuses1.png"

	EXPLOSION, //"assets/Sprite/Explosion"
	BIG_EXPLOSION, //"assets/Sprite/BigExplosion"

	BULLET1, //"assets/Sprite/ClassicBullet/ClassicBullet1.png"
	BULLET2, //"assets/Sprite/ClassicBullet/ClassicBullet2.png"
	BULLET3, //"assets/Sprite/ClassicBullet/ClassicBullet3.png"

	ENEMY1, //"assets/Sprite/Enemy1"
	ENEMY2,	//"assets/Sprite/Enemy2/Enemy2walk"
	ENEMY3	//"assets/Sprite/Enemy3"
};

#pragma pack(push, 4) //MSVC compatibility :$

template<typename T, auto toNet, auto toHost>
DECORATED_STRUCT(IntBase, {
	using	ValueType = T;

	IntBase() = default;
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

DECORATED_STRUCT(Ping, {
	PROTO_BASE(Type::PING)
});

DECORATED_STRUCT(UdpRegister, {
	PROTO_BASE(Type::UDP_REGISTER)
});

DECORATED_STRUCT(UdpConfirm, {
	PROTO_BASE(Type::UDP_CONFIRM)

	bool	status;
});

DECORATED_STRUCT(Move, {
	PROTO_BASE(Type::MOVE)

	Int32	componentId;
	Int32	x;
	Int32	y;
});

DECORATED_STRUCT(Create, {
	PROTO_BASE(Type::CREATE)

	Int32		componentId;
	Int32		w;
	Int32		h;
	Int32		x;
	Int32		y;
	SpriteId	spriteID;
});

DECORATED_STRUCT(Delete, {
	PROTO_BASE(Type::DELETE)

	Int32	componentId;
});

DECORATED_STRUCT(KeyPress, {
	PROTO_BASE(Type::KEYPRESS)

	std::uint8_t	keyCode;
});

DECORATED_STRUCT(KeyRelease, {
	PROTO_BASE(Type::KEYRELEASE)

	std::uint8_t	keyCode;
});

#pragma pack(pop)

#undef PROTO_BASE
#undef DECORATED_STRUCT

} // proto


#endif // _GAMEPROTOCOL_HPP
