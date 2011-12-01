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


static const char* VERSION = "0.1";


void showHelp (void);


int
main(int argc, char** argv)
{
    bool deamon = true;
    bool printConf = false;

    std::string configFile = "/etc/xzHTTPd/xzHTTPd.conf";

    int opt;
    while( (opt = getopt(argc, argv, "f:pDvh")) != -1)  {
        switch(opt)  {
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
                std::cout << "xzHTTPd v" << VERSION << std::endl;
                return 0;

            case 'h':
                showHelp();
                return 0;

            default:
                showHelp();
                return 0;
        }
    }
    
    xzHTTPd::Config::Config* serverConfig;
    xzHTTPd::Server::Server* server;

    try  {
        serverConfig = new xzHTTPd::Config::Config(configFile.c_str());

        if(printConf)  {
            std::cout << "" << std::endl;
            std::cout << "xzHTTPd configuration is 0 KILL!:" << std::endl;
            std::cout << "   ServerPort:\t\t"     << serverConfig->getParamVal("ServerPort") << std::endl;
            std::cout << "   MaxConnections:\t"   << serverConfig->getParamVal("MaxConnections") << std::endl;
            std::cout << "   DirHtdocs:\t\t"      << serverConfig->getParamVal("DirHtdocs") << std::endl;
            std::cout << "   FileIndex:\t\t"      << serverConfig->getParamVal("FileIndex") << std::endl;
            std::cout << "   DirLog:\t\t"         << serverConfig->getParamVal("DirLog") << std::endl;
            std::cout << "" << std::endl;
        }

        server = new xzHTTPd::Server::Server(serverConfig);
        server->start(deamon);

    } catch (xzHTTPd::Exception::Exception& e)  {
        std::cerr << e.what() << std::endl;
    }

    delete serverConfig;
    delete server;
    server = NULL;
    serverConfig = NULL;

    return 0;
}



void
showHelp(void)
{
    std::cout << "" << std::endl;
    std::cout << "xzHTTPd - Just a WebServer :3" << std::endl;
    std::cout << "" << std::endl;
    std::cout << "  Usage:" << std::endl;
    std::cout << "    -f <name>      Name of configuration file;"    << std::endl;
    std::cout << "    -p             Print the parsed config file;"  << std::endl;
    std::cout << "    -D             Do not deamonize;"              << std::endl;
    std::cout << "    -v             Print version;"                 << std::endl;
    std::cout << "    -h             Print this help."               << std::endl;
    std::cout << "" << std::endl;
}
