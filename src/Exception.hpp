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


#ifndef __XZHTTPD__EXCEPTION_HPP__
#define __XZHTTPD__EXCPETION_HPP__


#include <exception>
#include <string>


namespace xzHTTPd  {


namespace Exception {


class Exception : public std::exception
{
    public:

        static const unsigned int SOCKET_CREATE     = 1001;
        static const unsigned int SOCKET_ADDR_INIT  = 1002;
        static const unsigned int SOCKET_BIND       = 1003;
        static const unsigned int SOCKET_LISTEN     = 1004;

        static const unsigned int CONFIG_OPEN_FILE   = 2001;
        static const unsigned int CONFIG_PARSE_FILE  = 2002;

    public:

        Exception(unsigned int code =0);
        virtual ~Exception() throw();

        virtual const char* what() const throw();

    private:

        std::string desc;

        
};


}


}


#endif
