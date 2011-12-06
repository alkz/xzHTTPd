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


static
void
Server::start(bool deamon)
{
    if(deamon)  {
        if(fork())  {
            std::exit(0);
        } 
    }

    if ( chdir( Config::->getParamVal("DirHtdocs").c_str() ) == -1)  {
        throw ( Exception::Exception(Exception::Exception::SERVER_CHDIR) );
    }

    ServerSocket = new Socket();
    ServerSocket->bind( std::atoi(Config::->getParamVal("ServerPort").c_str()) );
    ServerSocket->listen( std::atoi(Config::->getParamVal("MaxConnections").c_str()) );

    while(1)  {
        PRThread* threadClient = NULL;
        threadClient = PR_CreateThread( 
                                         PR_USER_THREAD,
                                         processClient,
                                         ServerSocket->accept(),
                                         PR_PRIORITY_NORMAL,
                                         PR_LOCAL_THREAD,
                                         PR_JOINABLE_THREAD,
                                         0
                                      );

        if(! threadClient )  {
            throw ( Exception::Exception(Exception::Exception::SERVER_CREATE_THREAD) );
        }
        
        if (PR_JoinThread(threadClient) == PR_FAILURE)  {
            throw ( Exception::Exception(Exception::Exception::SERVER_JOIN_THREAD) );
        }
       
    }

}



static
void
Server::stop(void)
{
    if(ServerSocket)  {
        delete ServerSocket;
    }
    ServerSocket = NULL;
}



void
processClient(void* arg)
{
    try  {
        Client* client = new Client( static_cast<Socket*>(arg) );
        client->handleRequest();
        
        if(client)  {
            delete client;
        }
        client = NULL;
    } catch (Exception::Exception& e)  {
        std::cerr << e.what() << std::endl;
    }
    
}


}


}


#endif
