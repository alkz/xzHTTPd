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


#include "include/includer.hpp"


namespace xzHTTPd  {


namespace Config  {


#include <fstream>


class Config
{
    typedef   std::map<std::string, std::string>    Parameters;
    typedef   std::pair<std::string, std::string>   Parameter;

    public:

        Config(const char* );

        bool checkConf(void) const;
        bool parse(void);
        std::string getParamVal (std::string) const;
        std::string getFileName (void) const;

    private:

        bool inited;
        Parameters params;
        std::string fileName;

    private:

        
};


}


}


#endif
