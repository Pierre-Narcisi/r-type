/*
** EPITECH PROJECT, 2018
** r-type
** File description:
** _Network.hpp
*/


#if !defined(__NETWORK_HPP)
#define __NETWORK_HPP

#if defined _MSC_VER
 #include <io.h>
 #include <winsock2.h>
 #include <ws2tcpip.h>
 
 #define SOCKETCLOSE(fd) closesocket((fd))
 #define SOCKETIOCTL(fd, opts, ptr) ioctlsocket((fd), (opts), ((u_long*) ptr))

 using ssize_t = int;
 using Socket = SOCKET;
 #define SOCK_BUFFER_LEN_TYPE int
#else
 #include <sys/socket.h>
 #include <sys/types.h>
 #include <netinet/in.h>
 #include <netdb.h>
 #include <arpa/inet.h>
 #include <errno.h>
 #include <unistd.h>
 #include <sys/ioctl.h>

 #define SOCKETCLOSE(fd) ::close((fd))
 #define SOCKETIOCTL(args...) ::ioctl(args)
 #define SOCK_BUFFER_LEN_TYPE std::size_t

 using Socket = int;
#endif

#endif // __NETWORK_HPP
