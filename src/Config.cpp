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


#ifndef __XZHTTPD__CONFIG_CPP__
#define __XZHTTPD__CONFIG_CPP__ 


#include "include/Config.hpp"


namespace xzHTTPd  {


namespace Config  {


#include <algorithm>
#include <cstring>


Config::Config(const char* name)
{
    fileName = name;
    if(! (inited = parse()) )  {
        throw( Exception(Exception::CONFIG_PARSE_FILE) );
    }
}



bool
Config::checkConf(void)
{
    static const unsigned int NPAR = 5;
    // These words will be taken into the conf file
    static const char* parameterName[NPAR] = 
              { 
                "ServerPort",
                "MaxConnections",
                "DirHtdocs",
                "FileIndex",
                "DirLogs"
              };   
    
    std::ifstream f;     f.open(fileName, std::ios::ate);
    if(!f.is_open() || !f.tellg() )  {
        throw( Exception(Exception::CONFIG_OPEN_FILE) );
    }

    char buffer[400] = 0;
    bool isValid = false;

    f.seekg(0);
    do  {
        f.getline(buffer, sizeof(buffer), ' ');

        if(buffer[0] == '#')  {
            continue;
        }


        for (int i = 0; i < NPAR; i++)  {
            if(std::strcmp(parameterName[i], buffer) == 0)  {
                isValid = true;
                break;
            }
        }

        f.getline(buffer, sizeof(buffer));
    } while( (!f.eof()) && isValid);


    return isValid;
}



bool
Config::parse(void)
{
    if(! checkConf() )  {
        return false;
    }

    std::ifstream f;    f.open(fileName);
    if(! f.is_open() )  {
        throw( Exception(Exception::CONFIG_OPEN_FILE) );
    }

    char buffer[400] = 0;

    while(! f.eof())  {
        f.getline(buffer, sizeof(buffer), ' ');
        std::string paramName = buffer;
        f.getline(buffer, sizeof(buffer));
        std::string paramVal  = buffer;

        if(buffer[0] == '#')  {
            continue;
        }

        params.insert(Parameter(paramName, paramVal));
    }


    return true;
}



std::string
Config::getParamVal(std::string key)  const
{
    return (params[key]);
}



std::string
Config::getFileName(void)  const
{
    return (fileName);
}


}


}


#endif
