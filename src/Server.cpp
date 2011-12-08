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


Server::Server(Config::Config* conf)
{
    serverConf = conf;
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
    
    if ( chdir( serverConf->getParamVal("DirLog").c_str() ) == -1)  {
        throw ( Exception::Exception(Exception::Exception::LOG_DIR) );
    }

    logger = new Log::Logger( serverConf->getParamVal("DirLog") );
    Log::Logger& log = *logger;

    log << "[" << Utility::getTimeStamp() << "] - " << "Log inited! Start logging...\n";

    const char* htdocsDir = serverConf->getParamVal("DirHtdocs").c_str();

    if ( chdir( htdocsDir ) == -1)  {
        throw ( Exception::Exception(Exception::Exception::SERVER_CHDIR) );
    }

    log << "[" << Utility::getTimeStamp() << "] - " << "chdir to htdocs: " << htdocsDir << "\n";

    ServerSocket = new Socket();
    log << "[" << Utility::getTimeStamp() << "] - " << "Socket server inited\n";

    const char* port = serverConf->getParamVal("ServerPort").c_str();
    ServerSocket->bind( std::atoi(port) );
    log << "[" << Utility::getTimeStamp() << "] - " << "Socket Server binded to port: " << port << "\n";

    const char* maxC = serverConf->getParamVal("MaxConnections").c_str();
    ServerSocket->listen( std::atoi(maxC) );
    log << "[" << Utility::getTimeStamp() << "] - " << "Set Socket server max connections: " << maxC << "\n\n\n\n";

    while(1)  {
        ThreadData* data = new ThreadData(ServerSocket->accept(), serverConf, logger);
        PRThread* threadClient = NULL;
        threadClient = PR_CreateThread( 
                                         PR_USER_THREAD,
                                         processClient,
                                         data,
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
        ThreadData* data = static_cast<ThreadData*>(arg);
        Client* client = new Client(data->sock, data->conf, data->log);
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
