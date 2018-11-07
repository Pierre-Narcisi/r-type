/*
** EPITECH PROJECT, 2018
** babel
** File description:
** Const.hpp
*/

#pragma once

#include <string>

namespace constant {
    /* Server Program -- default args */
	constexpr std::uint16_t		defPort = 4242;

    /* Client Program -- default args */
#if !defined(NDEBUG)
    constexpr char const        *defHost = "localhost";
#else
    constexpr char const        *defHost = "holidev.net";
#endif
}
