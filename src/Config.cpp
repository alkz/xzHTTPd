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


#include "Config.hpp"


namespace xzHTTPd  {


namespace Config  {


Config::Config(const char* name)
{
    fileName = name;
    if(! parse() )  {
        throw( Exception::Exception(Exception::Exception::CONFIG_PARSE_FILE) );
    } 
}



bool
Config::parse(void)
{
    std::ifstream f;     f.open(fileName, std::ios::ate);
    if(!f.is_open() || !f.tellg() )  {
        throw( Exception::Exception(Exception::Exception::CONFIG_OPEN_FILE) );
    }

    char buffer[400];
    int paramCount = 0;

    f.seekg(0);
    do  {
        f.getline(buffer, sizeof(buffer));

        if(buffer[0] == '#' || strlen(buffer) == 0)  {
            continue;
        }

        char* token = std::strtok(buffer, " ");
        unsigned int n_tokens = 0;
        std::vector<const char*> par;

        while(token && (n_tokens < 3))  {
            n_tokens++;

            par.push_back(token);
            token = std::strtok(NULL, " ");
        }

        if(n_tokens > 2)  {
            return false;

        } else  {
            bool found = false;

            for(int i = 0; i < NPAR; i++)  {
                if( (std::strcmp(parameterName[i], par[0])) == 0)  {
                    paramCount++;
                    found = true;
                    break;
                }
            }

            if(!found)  {
                return false;
            } else  {
                params.insert( Parameter(std::string(par[0]), std::string(par[1])) );
            }
        }

        f.getline(buffer, sizeof(buffer));
    } while( !f.eof() );

    f.close();

    return ( (paramCount < NPAR) ? false : true );
}



std::string
Config::getParamVal(const std::string& key)  const
{
    return (params[key]);
}



const char*
Config::getFileName(void)  const
{
    return (fileName);
}


}


}


#endif
