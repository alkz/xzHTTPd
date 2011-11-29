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


#ifndef __XZHTTPD__SERVER_CPP__
#define __XZHTTPD__SERVER_CPP__ 


#include "Server.hpp"


namespace xzHTTPd  {


namespace Server  {


Server::Server(Config::Config* file)
{
    fileConf = new Config(file);
    inited = false;
}



bool
Server::init(void)
{
    if(!inited)  {
//        chdir(fileConf
        

        return true;
    } else  {
        return false;
    }

}


}


}


#endif
