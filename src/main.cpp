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


#include <iostream>
#include <getopt.h>


#include "Server.hpp"
#include "Config.hpp"


void showHelp (void);


int
main(int argc, char** argv)
{
    bool deamon = true;
    bool printConf = false;
    bool specifiedOp = false;

    std::string operation;
    std::string configFile = "/etc/xzHTTPd/xzHTTPd.conf";

    int opt;
    while( (opt = getopt(argc, argv, "o:f:pDvh")) != -1)  {
        switch(opt)  {
            case 'o':
                operation = optarg;
                specifiedOp = true;
                break;

            case 'f':
                configFile = optarg;
                break;

            case 'p':
                printConf = true;
                break;

            case 'D':
                deamon = false;
                break;

            case 'v':
                std::cout << "xzHTTPd v" << xzHTTPd::VERSION << std::endl;
                return 0;

            case 'h':
                showHelp();
                return 0;

            default:
                showHelp();
                return 0;
        }
    }

    if(!specifiedOp)  {
        showHelp();
        return 0;
    } 


    if(operation == "start")  {

        xzHTTPd::Config::Config* serverConfig = NULL;
        xzHTTPd::Server::Server* server = NULL;

        try  {
            serverConfig  = new xzHTTPd::Config::Config(configFile.c_str());

            if(printConf)  {
                std::cout << "" << std::endl;
                std::cout << "xzHTTPd configuration is 0 KILL!:" << std::endl;
                std::cout << "   ServerPort:\t\t"     << serverConfig->getParamVal("ServerPort")      << std::endl;
                std::cout << "   MaxConnections:\t"   << serverConfig->getParamVal("MaxConnections")  << std::endl;
                std::cout << "   DirHtdocs:\t\t"      << serverConfig->getParamVal("DirHtdocs")       << std::endl;
                std::cout << "   FileIndex:\t\t"      << serverConfig->getParamVal("FileIndex")       << std::endl;
                std::cout << "   DirLog:\t\t"         << serverConfig->getParamVal("DirLog")          << std::endl;
                std::cout << "   MimeDir:\t\t"        << serverConfig->getParamVal("MimeDir")         << std::endl;

                std::cout << std::endl << "Extensions Handlers: "                                     << std::endl;
                std::cout << "   php:\t\t"            << serverConfig->getExtHandler("php")           << std::endl;
                std::cout << std::endl;
            }


            server = new xzHTTPd::Server::Server(serverConfig);
            server->start(deamon);

        } catch (xzHTTPd::Exception::Exception& e)  {
            std::cerr << e.what() << std::endl;
        }

        if(serverConfig)  {
            delete serverConfig;
        }
        if(server)  {
            delete server;
        }
        server = NULL;
        serverConfig = NULL;
    } else  {
        std::cout << "Only start is avaliable, others operations haven't been supported yet :3" << std::endl;
    }

    return 0;
}



void
showHelp(void)
{
    std::cout << "" << std::endl;
    std::cout << "xzHTTPd - Just a WebServer :3" << std::endl;
    std::cout << "" << std::endl;
    std::cout << "  Usage:" << std::endl;
    std::cout << "    -o <operation>   {start | stop | restart};"                                           << std::endl;
    std::cout << "    -f <name>        Name of configuration file (default: /etc/xzHTTPd/xzHTTPd.conf);"    << std::endl;
    std::cout << "    -p               Print the parsed config file;"                                       << std::endl;
    std::cout << "    -D               Do not deamonize;"                                                   << std::endl;
    std::cout << "    -v               Print version;"                                                      << std::endl;
    std::cout << "    -h               Print this help."                                                    << std::endl;
    std::cout << "" << std::endl;
}
