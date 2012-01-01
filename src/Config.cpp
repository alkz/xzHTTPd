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

    char buffer[1024];
    unsigned int paramCount = 0;

    f.seekg(0);
    do  {
        f.getline(buffer, sizeof(buffer));

        if(buffer[0] == '#' || strlen(buffer) == 0)  {
            continue;
        }

        if(! explodeRow(buffer))  {
            return false;
        } else  {
            paramCount++;
        }


        f.getline(buffer, sizeof(buffer));
    } while( !f.eof() );

    f.close();

    return ( (paramCount < NPAR) ? false : true );
}



bool
Config::explodeRow(char* row)
{        
    enum rowType { PARAMETER, MODULE, OTHER };

    unsigned int n_token = 0;
    char* par[2];

    rowType type = OTHER;

    char* token = std::strtok(row, " ");
    while(token && (n_token < 2))  {

        if(! std::strcmp(token, "Parameter"))  {
            type = PARAMETER; 

        } else if(! std::strcmp(token, "Extension"))  {
            type = MODULE; 

        } else  {
            
            switch(type)  {

                case PARAMETER:
                    par[n_token] = new char[std::strlen(token)+1];
                    std::strcpy(par[n_token], token);
                    n_token++;

                    if(n_token == 2)  {
                        bool found = false;
                        for(unsigned int i = 0; i < NPAR; i++)  {
                            if(! std::strcmp(parameterName[i], par[0]))  {
                                found = true;
                                break;
                            }
                        }

                        if(!found)  {
                            return false;
                        } else  {
                            params.insert( Parameter(std::string(par[0]), std::string(par[1])) );
                            
                            type = OTHER;
                        }
                    }

                    break;

                case MODULE:
                    par[n_token] = new char[std::strlen(token)+1];
                    std::strcpy(par[n_token], token);
                    n_token++;

                    if(n_token == 2)  {
                        modules.insert( Module(std::string(par[0]), std::string(par[1])) );

                        type = OTHER;
                    }

                    break;

                default:   // WUT?
                    return false;
                
            }
        }
        
        token = std::strtok(NULL, " ");
    }

    return ( (n_token == 2) ? true : false );
}



std::string
Config::getParamVal(const std::string& key)  const
{
    return (params[key]);
}



std::string
Config::getExtHandler(const std::string& key)  const
{
    return (modules[key]);
}



const char*
Config::getFileName(void)  const
{
    return (fileName);
}


}


}


#endif
