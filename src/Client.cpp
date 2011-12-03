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

    Socket& socket = *clientSocket;
    socket >> request;


    // Bulding the response
    std::string headerResp;
    std::string resp;

    std::size_t begin = request.find_first_of("/");
    const char* fileName = request.substr(begin+1, request.find_first_of(" ", begin)-begin).c_str();

    const char* fileContent = getFileContent(fileName);

    if(! fileContent)  {
        headerResp = "HTTP/1.0 404 Not Found\r\nConnection: close\r\nContent-Type: text/html"
                     "\r\nServer: xzHTTPd\r\n\r\n";
        resp       = "<html><head><title>404 - Gaypride</title></head>"
                     "<body><h2>404 - Page not found gay</h2><hr />"
                     "<i>xzHTTPd v";
        resp      += VERSION;
        resp      += "</i></body></html>";

        socket << headerResp << resp;
    } else  {
    }
}



const char*
Client::getFileContent(const char* name)
{
    std::ifstream f;     f.open(name);
    if( !f.is_open() )  {
        return NULL;
    }
    
}


}


}


#endif
