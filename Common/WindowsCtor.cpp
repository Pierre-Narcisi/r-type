/*
** EPITECH PROJECT, 2018
** r-type
** File description:
** WindowsCtor.cpp
*/

#if defined _MSC_VER

#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include "ctor.h"
#pragma comment(lib, "ws2_32.lib")

static WSADATA wsaData;

#ifdef HAS_CONSTRUCTORS
CONSTRUCTOR(initWSA)
DESTRUCTOR(closeWSA)
#else
#ifdef _MSC_VER
static void initWSA(void);
static void closeWSA(void);
#pragma data_seg(".CRT$XCU")
static void (*msc_ctor)(void) = initWSA;
#pragma data_seg(".CRT$XPU")
static void (*msc_dtor)(void) = closeWSA;
#pragma data_seg()
#endif
#endif

void initWSA()
{
	auto res = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (res != 0) {
        std::cerr << "WSAStartup failed with error: " << res << std::endl;
		exit(84);
    }
}
 
void closeWSA()
{
	WSACleanup();
}

#endif