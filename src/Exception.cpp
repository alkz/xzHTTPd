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


#ifndef __XZHTTPD__EXCEPTION_CPP__
#define __XZHTTPD__EXCEPTION_CPP__


#include "Exception.hpp"


namespace xzHTTPd  {


namespace Exception  {


Exception::Exception(unsigned int code)
{
    switch(code)  {
        case SOCKET_CREATE:
            desc = "Could not create Socket.";
            break;

        case SOCKET_ADDR_INIT:
            desc = "Could not initialize address.";
            break;

        case SOCKET_BIND:
            desc = "Could not bind the socket to address.";
            break;

        case SOCKET_LISTEN:
            desc = "Could not put the socket on listening.";
            break;
            
        case SOCKET_RECV:
            desc = "Error while reading the socket buffer.";
            break;

        case SOCKET_RECV_CLOSED:
            desc = "Error while reading the socket buffer, connection was closed.";
            break;

        case SOCKET_ACCEPT:
            desc = "Could not connect the incoming connecion.";
            break;

        case SOCKET_CLOSE:
            desc = "Could not close socket.";
            break;

        case SOCKET_SEND:
            desc = "Error while sending data in the socket.";
            break;

        case CONFIG_OPEN_FILE:
            desc = "Could not open config file.";
            break;

        case CONFIG_PARSE_FILE:
            desc = "Error while parsing conf file (syntax error).";
            break;

        case SERVER_START:
            desc = "Could not start xzHTTPd.";
            break;

        case SERVER_CREATE_THREAD:
            desc = "Could not create a new thread for client connected";
            break;

        case SERVER_JOIN_THREAD:
            desc = "Could not join the client thread.";
            break;

        case SERVER_CHDIR:
            desc = "Failed to chdir to htdocs directory, check permissions and if the dir exists.";
            break;

        case SERVER_WRONG_USER:
            desc = "Failed to start xzHTTPd, you should start it from xzhttpd user.";
            break;

        case LOG_OPEN_FILE:
            desc = "Failed to open log file.";
            break;

        case LOG_DIR:
            desc = "Failed to chdir to log directory, check permissions and if the dir exists.";
            break;

        case MIME_OPEN_FILE:
            desc = "Could not open MimeTypes file.";
            break;

        default:
            desc = "You did something wrong.";
    }

}



Exception::~Exception() throw()
{
}



const char*
Exception::what() const throw()
{
    return desc.c_str();
}


}


}


#endif
