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


#ifndef __XZHTTPD__CLIENT_CPP__
#define __XZHTTPD__CLIENT_CPP__ 


#include "Client.hpp"


namespace xzHTTPd  {


namespace Server  {


Client::Client(Socket* sock)
{
    clientSocket = sock;
}



Client::~Client()
{
    if(clientSocket)  {
        delete clientSocket;
    }
    clientSocket = NULL;
}



void
Client::handleRequest(void)
{
    request = clientSocket->recv();
    std::cout << request << std::endl;
    std::string s = "HTTP/1.0 200 OK\r\nContent-Type: text/html\r\n\r\n";
    s += "<html><head><title>xzHTTPd ";
    s +=  VERSION;
    s +=  "</title></head><body><h1>It works mudafucka!</h1></body></html>";

    clientSocket->send(s);
}



}


}


#endif
