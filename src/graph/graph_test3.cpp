#include "createGrpAdjLinkedList.h"
// #include "createGrpAdjMatrix.h"
#include <crtdbg.h>
#include <direct.h>

#include <iostream>
#include <string>
#include <vector>
char cwd[1024];

int firstadj(Graph g, elementType tar1)
{
    // 找到tar1的指针即可
    VertexNode tar1_node;
    for (int i = 1; i <= 26; i++)
    {
        if (g.VerList[i].data == tar1)
        {
            tar1_node = g.VerList[i];
        }
    }
    return tar1_node.firstEdge->adjVer;
}
int nextadj(Graph g, elementType tar1, elementType tar2)
{
    VertexNode tar1_node;
    for (int i = 1; i <= 26; i++)
    {
        if (g.VerList[i].data == tar1)
        {
            tar1_node = g.VerList[i];
        }
    }
    EdgeNode* curr_edge = tar1_node.firstEdge;
    while (curr_edge->next != nullptr)
    {
        eInfoType curr_ind = curr_edge->adjVer;
        if (g.VerList[curr_ind].data == tar2)
        {
            return curr_edge->next->adjVer;
        }
        curr_edge = curr_edge->next;
    }
    return -1;
}
int main()
{
    _getcwd(cwd, sizeof(cwd));
    std::string data_dir_path = std::string(cwd) + "/../src/graph/grpData/";
    std::string data_name = "udg8.grp";
    std::string data_path_str = data_dir_path + data_name;
    char* data_path = new char[data_path_str.size() + 1];
    // std::strncpy(data_path,data_path_str.c_str(),sizeof(data_path)-1);
    std::strcpy(data_path, data_path_str.c_str());
    Graph g;
    if (CreateGraphFromFile(data_path, g))
    {
        char tar1 = 'a';
        char tar2 = 'b';
        std::cout << tar1 << " 调用firstadj的结果是 " << firstadj(g, tar1);
        std::cout << "\n";
        std::cout << tar1 << "在" << tar2 << "后的下一个是" << nextadj(g, tar1, tar2);
    }
    else
    {
        std::cout << "create:fail" << "\n";
    };
}
