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


#ifndef __XZHTTPD__UTILITY_CPP__
#define __XZHTTPD__UTILITY_CPP__ 


#include "Utility.hpp"


namespace xzHTTPd  {


namespace Server  {


std::string
Utility::getMimeType(const std::string& ext)
{
    std::size_t beginExt = ext.find_first_of(".", 1);
    std::string type = ext.substr(
                                  beginExt+1, 
                                  ext.find_first_of(
                                                      beginExt, 
                                                      ext.find_first_of(" ", beginExt) - beginExt
                                                   )
                               );

    for(int i = 0; Extensions[i].ext != 0; i++)  {
        if( ! std::strcmp(Extensions[i].ext, type.c_str()) )  {
            type = Extensions[i].contenType;
            break;
        }
    }

    return type;
}



std::string
Utility::getTimeStamp(void)
{
    std::time_t result = std::time(NULL);
    char* t = std::asctime(std::localtime(&result));
    std::string timestamp(t, std::strlen(t) - 1);

    return timestamp;
}


}


}


#endif
