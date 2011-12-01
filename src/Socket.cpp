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


#include "Socket.hpp"


namespace xzHTTPd  {


namespace Server  {


Socket::Socket(bool init)
{
    if(init)  {
        if(! (sock = PR_NewTCPSocket()) )  {
            throw ( Exception::Exception(Exception::Exception::SOCKET_CREATE) ); 
        } 
    }
}



Socket::~Socket()
{
    delete sock;
    delete addr;
    sock = NULL;
    addr = NULL;
}



void
Server::Socket::bind(unsigned int port)
{
    addr = new PRNetAddr;

    if( (PR_InitializeNetAddr(PR_IpAddrAny, port, addr) == PR_FAILURE ) )  {
        throw ( Exception::Exception(Exception::Exception::SOCKET_ADDR_INIT) );
    }

    if( (PR_Bind(sock, addr)) == PR_FAILURE )  {
        throw ( Exception::Exception(Exception::Exception::SOCKET_BIND) );
    }
}



void
Socket::listen(unsigned int maxConnections)
{
    if( (PR_Listen(sock, maxConnections) == PR_FAILURE) )  {
        throw ( Exception::Exception(Exception::Exception::SOCKET_LISTEN) );
    }
}



Socket* 
Socket::accept(void)
{
    Socket* client = new Socket(false);
    client->sock = PR_Accept(server, client->addr, PR_INTERVAL_NO_TIMEOUT);

    return (this);
}



std::string
Socket::recv(void)
{
    std::string toReturn;
    char* buffer[2000];


    // ...
}


}


}


#endif
