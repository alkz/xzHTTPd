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


#ifndef __XZHTTPD__LOG_CPP__
#define __XZHTTPD__LOG_CPP__ 


#include "Log.hpp"


namespace xzHTTPd  {


namespace Log  {


Logger::Logger(const std::string& path)
{
    std::string back = "log.";
    std::string lastLog;
    bool full = true;
    std::string tmpFile;

    std::cout << "nig";
    for(char i = '0'; i <= '9'; i++)  {
        lastLog = back + i;
        std::ifstream f;    
        tmpFile = path + "/" + lastLog;
        f.open(tmpFile.c_str());
        if(! f.is_open())  {
            full = false;
            break;
        }
    }

    nameLogFile = ( (!full) ? tmpFile : ( path + "/log.0" ) );
    logFile.open(nameLogFile.c_str(), std::ios::binary);

    if(! logFile.is_open() )  {
        throw ( Exception::Exception(Exception::Exception::LOG_OPEN_FILE) );
    }

}



Logger::~Logger()
{
    logFile.flush();
    logFile.close();
}



void
Logger::write(const std::string& str)
{
    logFile.write(str.c_str(), str.length());
    logFile.flush();

    if(logFile.bad())  {
        throw ( Exception::Exception(Exception::Exception::LOG_WRITE) );
    }
}



Logger&
Logger::operator <<(const std::string& str)
{
    this->write(str);

    return *this;
}


}


}


#endif
