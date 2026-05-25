// #include "createGrpAdjLinkedList.h"
#include "createGrpAdjMatrix.h"
#include <string>
#include <iostream>
#include <direct.h>
#include <crtdbg.h>
#include <vector>
char cwd[1024];

int main()
{
    _getcwd(cwd,sizeof(cwd));
    std::string data_dir_path = std::string(cwd) + "/../src/graph/grpData/";
    std::string data_name = "udg8.grp";
    std::string data_path_str = data_dir_path + data_name;
    char * data_path = new char[data_path_str.size()+1];
    std::strncpy(data_path,data_path_str.c_str(),sizeof(data_path)-1);
    Graph g;
    if( CreateGrpFromFile(data_path,g))
    {
        std::cout << g.ArcNum;
    }
    else
    {
        std::cout << "create:fail" << "\n";
        std::cout << data_path << std::endl;
        std::cout << "你好";
    };
}
