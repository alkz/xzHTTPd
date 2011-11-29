#include <iostream>
#include "Config.hpp"

using namespace xzHTTPd;

int
main(int argc, char** argv)
{
    if(argc < 2)  {
        std::cout << "gay" << std::endl;
        return -1;
    }

    Config::Config* myConfig = new Config::Config(argv[1]);
    std::cout << myConfig->getParamVal("ServerPort") << std::endl;


    return 0;
}



