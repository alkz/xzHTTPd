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


#ifndef __XZHTTPD__SOCKET_HPP__
#define __XZHTTPD__SOCKET_HPP__


#include "include/includer.hpp"


namespace xzHTTPd  {


namespace Server  {


#include <prnetdb.h>


class Socket
{
    public: 

        Socket(unsigned int, unsigned int);
        ~Socket();

        std::string recv(void);
        bool send(std::string);


    private:

        bool listen(void);
        bool bind  (void);
        

    private:

        PRFileDesc* sock;
        PRNetAddr*  addr;
        
};

    
}


}


#endif
