/*
** EPITECH PROJECT, 2018
** r-type
** File description:
** WindowsCtor.cpp
*/

#if defined _MSC_VER

#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <iostream>
#pragma comment(lib, "ws2_32.lib")

static WSADATA wsaData;

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

#else

void initWSA() {}
void closeWSA() {}

#endif