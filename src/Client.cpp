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


#include "Client.hpp"


namespace xzHTTPd  {


namespace Server  {


Client::Client(Socket* sock, Config::Config* conf, Log::Logger* log)
{
    clientSocket = sock;
    serverConf = conf;
    logger = log;
}



Client::~Client()
{
    if(clientSocket)  {
        delete clientSocket;
    }
    clientSocket = NULL;
    serverConf = NULL;
    logger = NULL;
}



void
Client::handleRequest(void)
{
    Socket& socket = *clientSocket;
    Log::Logger& log = *logger;

    socket >> request;

    log << "[" << Utility::getTimeStamp() << "]" << "\nRequest from: " << clientSocket->getAddress() << "\n\n" << request << "\n\n";

    // Bulding the response
    std::string fileName = getFileName();
    std::string content = getFileContent(fileName);

    HTTPResponse* response = new HTTPResponse();

    if(! content.length())  {
        response->setHeader("Connection",    "close");
        response->setHeader("Content-Type",  "text/html");
        response->setHeader("Server",        "xzHTTPd");
        response->setStatus(404); 
        content   =  "<html><head><title>404 - Gaypride</title></head>"
                     "<body><h2>404 - Page not found gay</h2><hr />"
                     "<i><h5>xzHTTPd v";
        content  +=  VERSION;
        content  +=  " - 2011</h5></i></body></html>";
        response->setContent(content);

        socket << response->getHeader() << response->getContent();
        log << "[" << Utility::getTimeStamp() << "]" << "\nResponse: \n" << response->getHeader() << "\n\n";

    } else  {
        std::string ext = getExtension(fileName);

        if(serverConf->getExtHandler(ext) == "default")  {
        }

        response->setHeader( "Content-Type",   serverConf->getMimeType(ext) );
        response->setHeader("Server",         "xzHTTPd");
        response->setMethod( request.substr( 0, request.find_first_of(" ") ) );
        response->setStatus(200);

        response->setContent(content);

        socket << response->getHeader() << response->getContent();
        log << "[" << Utility::getTimeStamp() << "]" << "\nResponse: \n" << response->getHeader() << fileName << "\n\n\n\n";
    }

}



std::string
Client::getFileName() const
{
    std::size_t begin = request.find_first_of("/");
    std::string fileName = request.substr(
                                           begin, 
                                           request.find_first_of(" ?", begin) - begin
                                         ).insert(0, ".");

    if(fileName.length() == 2)  {    // Faggot user didn't give a page name (length == "./")
        char* tmp = new char[serverConf->getParamVal("FileIndex").length()+1];
        std::strcpy(tmp, serverConf->getParamVal("FileIndex").c_str());
        char* s = std::strtok(tmp, ",");
        while(s)  {
            std::ifstream f;    f.open(s);
            if(f.is_open())  {
                return ( fileName + s );
            }
            s = std::strtok(NULL, ",");
        }
        
        delete [] tmp;
    }

    return fileName;
}



std::string
Client::getFileContent(const std::string& name) const
{
    std::ifstream f;     f.open(name.c_str(), std::ios::binary);
    if( !f.is_open() )  {
        return (std::string(""));

    }  else  { 
        f.seekg(0, std::ios::end);
        long int length = f.tellg(); 
        f.seekg(0, std::ios::beg);

        char* buffer = new char[length];    // Fuck yea
        f.read(buffer, length);             // Double fuck yea

        f.close();

        return ( std::string(buffer, buffer + length) );
    }
    
}



std::string
Client::getExtension(const std::string& filename) const
{
    std::size_t beginExt = filename.find_first_of(".", 1);
    std::string type = filename.substr(
                                  beginExt+1, 
                                  filename.find_first_of(
                                                      beginExt, 
                                                      filename.find_first_of(" ", beginExt) - beginExt
                                                   )
                                 );

    return type;
}


}


}
