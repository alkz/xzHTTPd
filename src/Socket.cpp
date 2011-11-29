/****************************************************************************
* This file is part of xzHTTPd.                                             *
* Copyleft alkz                                                             *
*                                                                           *
* xzHTTPd is free software: you can redistribute it and/or modify           *
* it under the terms of the GNU General Public License as published by      *
* the Free Software Foundation, either version 3 of the License, or         *
* (at your option) any later version.                                       *
*                                                                           *
* xzHTTPd is distributed in the hope that it will be useful.                *
* but WITHOUT ANY WARRANTY; without even the implied warranty o.            *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See th.              *
* GNU General Public License for more details.                              *
*                                                                           *
* You should have received a copy of the GNU General Public License         *
* along with xzHTTPd. If not, see <http://www.gnu.org/licenses/>.           *
****************************************************************************/


#ifndef __XZHTTPD__SOCKET_CPP__
#define __XZHTTPD__SOCKET_CPP__


#include "include/Socket.hpp"


namespace zxHTTPd  {


namespace Server  {


Socket::Socket(unsigned int port, unsigned int maxConnections)
{
    addr = new PRNetAddr;

    if(! (sock = PR_NewTCPSocket()) )  {
        throw ( Exception(Exception::SOCKET_CREATE) ); 
    } 

    if( (PR_InitializeNetAddr(PR_IpAddrAny, port, addr) == PR_FAILURE )  {
        throw ( Exception(Exception::SOCKET_ADDR_INIT) );
    }

    bind(port);
    listen(maxConnections);
}



Socket::~Socket()
{
    delete sock;
    delete addr;
    sock = NULL;
    addr = NULL;
}



bool
Socket::bind(unsigned int port)
{
    if( (PR_Bind(sock, addr)) == PR_FAILURE )  {
        throw ( Exception(Exception::SOCKET_BIND) );
    }
}



bool
Socket::listen(unsigned int maxConnections)
{
    if( (PR_Listen(sock, maxConnections) == PR_FAILURE )  {
        throw ( Exception(Exception::SOCKET_LISTEN) );
    }
}



std::string
Socket::recv(void)
{
    std::string toReturn;
    char* buffer[2000];


}


}


}


#endif
