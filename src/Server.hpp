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


#include <unistd.h>
#include <cstdlib>
#include <prthread.h>
#include <prnetdb.h>
#include <cstdlib>


#include "includer.hpp"
#include "Config.hpp"
#include "Socket.hpp"
#include "Client.hpp"


namespace xzHTTPd  {


namespace Server  {


// This will be passed to the client thread
struct ThreadData  {

    ThreadData(Socket* s, Config::Config* c, Log::Logger* l) : 
         sock(s), conf(c), log(l)
    {
    }

    Socket*         sock;
    Config::Config* conf;
    Log::Logger*    log;
};


class Server
{

    public:

        Server(Config::Config*);
        ~Server();

        void start(bool);
        void stop (void);

    private:

        std::string getTimeStamp(void);

    private:

        Config::Config* serverConf;
        Socket* ServerSocket;
        Log::Logger* logger;
        
};


void processClient(void*);


}


}


#endif
