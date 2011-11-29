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


#ifndef __XZHTTPD__SERVER_HPP__
#define __XZHTTPD__SERVER_HPP__ 


#include "include/includer.hpp"


namespace xzHTTPd  {


namespace Server  {


class Server
{
    public:
        
        Server(Config::Config);

        bool init (void);
        bool start(void);
        bool stop (void);


    private:

        bool inited;
        Config::Config fileConf;

        
};


}


}


#endif
