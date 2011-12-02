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
    ServerConf = file;
}



Server::~Server()
{
    delete ServerSocket;
    ServerSocket = NULL;
}



void
Server::start(bool deamon)
{
    if(deamon)  {
        if(fork())  {
            std::exit(0);
        } 
    }

    chdir( ServerConf->getParamVal("DirHtdocs").c_str() );
    std::cout << "cd " << ServerConf->getParamVal("DirHtdocs") << " - 0 KILL" << std::endl; 

    ServerSocket = new Socket();
    ServerSocket->bind( std::atoi(ServerConf->getParamVal("ServerPort").c_str()) );
    ServerSocket->listen( std::atoi(ServerConf->getParamVal("MaxConnections").c_str()) );

    while(1)  {
        PRThread* threadClient;
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


void
processClient(void* arg)
{
    Client* client = new Client( static_cast<Socket*>(arg) );
    client->handleRequest();

    delete client;
}


}


}


#endif
