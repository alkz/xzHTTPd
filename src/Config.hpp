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


#ifndef __XZHTTPD__CONFIG_HPP__
#define __XZHTTPD__CONFIG_HPP__ 


#include <fstream>
#include <map>
#include <string>
#include <cstring>
#include <vector>


#include "Exception.hpp"


namespace xzHTTPd  {


namespace Config  {


class Config
{
    typedef   std::map<std::string, std::string>    Parameters;
    typedef   std::pair<std::string, std::string>   Parameter;

    public:

        Config(const char* );
        Config(const Config&);

        bool parse(void);
        std::string& getParamVal (const std::string&) const;
        const char* getFileName (void) const;
        bool isInited(void) const;

    private:

        mutable Parameters params;
        bool inited;
        const char* fileName;
        
};


}


}


#endif
