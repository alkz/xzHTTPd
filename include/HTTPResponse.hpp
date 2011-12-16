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


#ifndef __XZHTTPD__HTTP_RESPONSE_HPP__
#define __XZHTTPD__HTTP_RESPONSE_HPP__


#include <map>
#include <sstream>
#include <vector>


#include "includer.hpp"


namespace xzHTTPd  {


namespace Server  {


class HTTPResponse
{
    typedef    std::map< std::string, std::string >     HTTPHeader;
    typedef    std::pair< std::string, std::string >    HTTPHeaderField;

    typedef    std::map< unsigned int, std::string >    StatusCodes;

    public:

        HTTPResponse();

        void setHeader  (const std::string&, const std::string&);
        void setStatus  (unsigned int);
        void setHTTPVersion (const std::string&);
        void setContent (const std::string&);
        void setMethod(const std::string&);

        std::string getHeader (void);
        std::string getHeaderFiled(const std::string&) const;
        std::string getContent(void) const;
        unsigned int getStatus(void) const;
        std::string getVersion(void) const;
        std::string getMethod(void) const;
        std::string getHeaderField(const std::string&);

    private:

        void initStatusCodes(void);
        
    private:

        HTTPHeader header;
        std::string content;

        StatusCodes codes;
        unsigned int currentStatus;
        std::string HTTPVersion;
        std::string method;

};


}


}


#endif
