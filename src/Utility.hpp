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


#ifndef __XZHTTPD__UTILITY_HPP__
#define __XZHTTPD__UTILITY_HPP__ 


#include <ctime>


#include "includer.hpp"


namespace xzHTTPd  {


namespace Server  {


struct MimeT {
	const char *ext;
	const char *contenType;
}; 


static const struct MimeT Extensions [] =  {
                               {"gif",   "image/gif" },  
                               {"jpg",   "image/jpeg"}, 
                               {"jpeg",  "image/jpeg"},
                               {"png",   "image/png" },  
                               {"zip",   "image/zip" },  
                               {"gz",    "image/gz"  },  
                               {"tar",   "image/tar" },  
                               {"htm",   "text/html" },  
                               {"html",  "text/html" },  
                               {"css",   "text/css" },  

                               {0,0} 
                             };


class Utility
{
    public:

        static std::string getMimeType(const std::string&);
        static std::string getTimeStamp(void);

};


}


}


#endif
