#include "createGrpAdjLinkedList.h"
// #include "createGrpAdjMatrix.h"
#include <crtdbg.h>
#include <direct.h>

#include <iostream>
#include <string>
#include <vector>
char cwd[1024];
bool visited[100];
int bt[100][100];
void dfs(Graph g, int ind)
{
    visited[ind] = true;
    EdgeNode* p = g.VerList[ind].firstEdge;
    while (p != nullptr)
    {
        if (!visited[p->adjVer])
        {
            bt[ind][p->adjVer] = 1;
            bt[p->adjVer][ind] = 1;
            dfs(g, p->adjVer);
        }
        p = p->next;
    }
}
int main()
{
    _getcwd(cwd, sizeof(cwd));
    std::string data_dir_path = std::string(cwd) + "/../src/graph/grpData/";
    std::string data_name = "udg10.grp";
    std::string data_path_str = data_dir_path + data_name;
    char* data_path = new char[data_path_str.size() + 1];
    // std::strncpy(data_path,data_path_str.c_str(),sizeof(data_path)-1);
    std::strcpy(data_path, data_path_str.c_str());
    Graph g;
    if (CreateGraphFromFile(data_path, g))
    {
        dfs(g, 1);
        for (int i = 1; i <= g.VerNum; i++)
        {
            for (int j = 1; j <= g.VerNum; j++)
            {
                std::cout << bt[i][j] << " ";
            }
            std::cout << "\n";
        }
    }
    else
    {
        std::cout << "create:fail" << "\n";
    };
}
