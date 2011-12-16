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


#ifndef __XZHTTPD__HTTP_contentONSE_CPP__
#define __XZHTTPD__HTTP_contentONSE_CPP__


#include "HTTPResponse.hpp"


namespace xzHTTPd  {


namespace Server  {


HTTPResponse::HTTPResponse()
{
    initStatusCodes();
    HTTPVersion = "1.0";    // Default Version
}



void
HTTPResponse::setHeader(const std::string& key, const std::string& value)
{
    this->header.insert( HTTPHeaderField(key, value) );
}



void
HTTPResponse::setStatus(unsigned int code)
{
    this->currentStatus = code;
}



void 
HTTPResponse::setHTTPVersion(const std::string& version)
{
    this->HTTPVersion = version;
}



void
HTTPResponse::setContent(const std::string& _content)
{
    this->content = _content;

    std::stringstream ss;
    ss << content.length();

    setHeader( "Content-Length", ss.str());
}



void
HTTPResponse::setMethod(const std::string& _method)
{
    this->method = _method;
}



std::string
HTTPResponse::getHeader(void)
{
    std::string toReturn;
    toReturn += "HTTP/" + this->HTTPVersion + " " + this->codes[currentStatus] + "\r\n";

    HTTPHeader::const_iterator HI;
    for(HI = header.begin(); HI != header.end(); HI++)  {
        toReturn += HI->first + ": " + HI->second + "\r\n";
    }
    toReturn += "\r\n";

    return toReturn;
}



std::string 
HTTPResponse::getHeaderField(const std::string& key)
{
    return (header[key]);
}



std::string
HTTPResponse::getContent(void) const
{
    return content;
}



unsigned int
HTTPResponse::getStatus(void) const
{
    return currentStatus;
}



std::string
HTTPResponse::getVersion(void) const
{
    return HTTPVersion;
}



std::string
HTTPResponse::getMethod(void) const
{
    return method;
}



void
HTTPResponse::initStatusCodes(void)
{
    // I should put even others but I'm lazy :3
    
    codes[200] = "200 OK";

    codes[404] = "404 Not Found";
}


}


}


#endif
