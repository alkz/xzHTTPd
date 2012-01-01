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
#include <vector>


#include "includer.hpp"


namespace xzHTTPd  {


namespace Config  {


static const unsigned int NPAR = 5;
static const char parameterName[][15] = 
          { 
            "ServerPort",
            "MaxConnections",
            "DirHtdocs",
            "FileIndex",
            "DirLog"
          };   


class Config
{
    typedef   std::map <std::string, std::string>   Parameters;
    typedef   std::map <std::string, std::string>   Modules;

    typedef   std::pair<std::string, std::string>   Parameter;
    typedef   std::pair<std::string, std::string>   Module;

    public:

        Config(const char* );

        std::string getParamVal   (const std::string&) const;
        std::string getExtHandler (const std::string&) const;
        const char* getFileName   (void) const;

    private:
        
        bool parse(void);
        bool explodeRow(char*);

    private:

        mutable Parameters params;
        mutable Modules modules;
        const char* fileName;
        
};


}


}


#endif
