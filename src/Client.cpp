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

    std::string fileName = getFileName();
    std::string fileContent = getFileContent(fileName);
    std::cout << fileContent << std::endl;

    if(! fileContent.length())  {
        headerResp = "HTTP/1.0 404 Not Found\r\nConnection: close\r\nContent-Type: text/html"
                     "\r\nServer: xzHTTPd\r\n\r\n";

        std::string resp;
        resp       = "<html><head><title>404 - Gaypride</title></head>"
                     "<body><h2>404 - Page not found gay</h2><hr />"
                     "<i><h5>xzHTTPd v";
        resp      += VERSION;
        resp      += "</h5></i></body></html>";

        socket << headerResp << resp;

    } else  {
        std::string contenType = MimeType::getMimeType(fileName);
        headerResp = "HTTP/1.0 200 OK\r\nContent-Type: " + contenType;
        headerResp += "\r\nServer: xzHTTPd\r\n\r\n";
        socket << headerResp << fileContent;
    }
}



std::string
Client::getFileName(void)
{
    std::size_t begin = request.find_first_of("/");
    std::string fileName = request.substr(
                                           begin, 
                                           request.find_first_of(" ", begin) - begin
                                         ).insert(0, ".");

    return fileName;
}



std::string
Client::getFileContent(const std::string& name)
{
    std::ifstream f;     f.open(name.c_str(), std::ios::binary);
    if( !f.is_open() )  {
        return (std::string(""));

    }  else  { 
        f.seekg(0, std::ios::end);
        unsigned int length = f.tellg(); 
        f.seekg(0, std::ios::beg);

        char* buffer = new char[length];    // Fuck yea
        f.read(buffer, length);             // Double fuck yea

        f.close();

        return ( std::string(buffer) );
    }
    
}


}


}

#endif
