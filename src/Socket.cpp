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


#include "Socket.hpp"


namespace xzHTTPd  {


namespace Server  {


Socket::Socket(bool init)
{
    sock = NULL;
    addr = NULL;

    if(init)  {
        if(! (sock = PR_NewTCPSocket()) )  {
            throw ( Exception::Exception(Exception::Exception::SOCKET_CREATE) ); 
        } 
    }
}



Socket::~Socket()
{
    close();
    if(addr)  {
        delete addr;
    }
    sock = NULL;
    addr = NULL;
}



void
Socket::bind(unsigned int port)
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
    Socket* client  = new Socket(false);
    client->addr = new PRNetAddr;

    if (! (client->sock = PR_Accept(this->sock, client->addr, PR_INTERVAL_NO_TIMEOUT)) )  {
        throw ( Exception::Exception(Exception::Exception::SOCKET_ACCEPT) );
    }

    return client;
}



void
Socket::close(void)
{
    if( PR_Close(sock) == PR_FAILURE )  {
        throw( Exception::Exception(Exception::Exception::SOCKET_CLOSE) );
    }
}



std::string
Socket::recv(void)
{
    char buffer[800] = "\0";
    std::string toReturn;
    std::size_t len;

    do  {
        std::strcpy(buffer, "\0");
        PRInt32 res = PR_Recv(sock, buffer, sizeof(buffer), 0, PR_INTERVAL_NO_WAIT);

        len = std::strlen(buffer);

        if(res == -1 && len != 0)  {
            throw ( Exception::Exception(Exception::Exception::SOCKET_RECV) );
        }  else if (res == 0 && len != 0) {
            throw ( Exception::Exception(Exception::Exception::SOCKET_RECV_CLOSED) );
        } 

        if(len)  {
            toReturn.insert(toReturn.length(), buffer);
        }
    } while(len);

    return toReturn;
}



void
Socket::send(const std::string& s)
{
    if(PR_Send(sock, s.c_str(), s.length(), 0, PR_INTERVAL_NO_WAIT) == -1)  {
        throw ( Exception::Exception(Exception::Exception::SOCKET_SEND) );
    }
}



std::string
Socket::getAddress(void)
{
    char buf[20];
    PR_NetAddrToString(addr, buf, sizeof(buf));

    return (std::string(buf));
}



Socket&
Socket::operator <<(const std::string& s)
{
    this->send(s);

    return *this;
}



Socket&
Socket::operator >>(std::string& s)
{
    s = this->recv();

    return *this;
}


}


}
