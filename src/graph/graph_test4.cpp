#include "createGrpAdjLinkedList.h"
// #include "createGrpAdjMatrix.h"
#include <crtdbg.h>
#include <direct.h>

#include <iostream>
#include <string>
#include <vector>
char cwd[1024];
// 检查根节点入度是否为0
// 检查其他节点入度是否为1
bool visited[100];
void dfs(Graph g, int ind)  // 递归涂颜色
{
    visited[ind] = true;
    EdgeNode* p = g.VerList[ind].firstEdge;
    while (p != nullptr)
    {
        if (visited[p->adjVer] == false)
        {
            dfs(g, p->adjVer);  // 不要传next，因为p已经是边了
        }
        p = p->next;
    }
}
int in_degree[27];
bool judge(Graph g, elementType root_ch)
{
    int root_ind = 1;
    VertexNode* root_ptr;
    for (int i = 1; i <= g.VerNum; i++)
    {
        // 检查每个点的入度，因为是对边操作，所以迭代用边
        // 顺便找根节点的序号
        // VertexNode cur = g.VerList[i];
        EdgeNode* cur = g.VerList[i].firstEdge;
        if (g.VerList[i].data == root_ch)
        {
            root_ind = i;
            root_ptr = &g.VerList[i];
        }
        while (cur != nullptr)  // 如果用26硬编码的话，会拦不住，因为此时cur这个edge可能是随机值
        {
            in_degree[cur->adjVer]++;
            cur = cur->next;
        }
    }
    if (in_degree[root_ind] != 0)  // 根节点入度为0
    {
        return false;
    }
    for (int i = 1; i <= g.VerNum; i++)  // 其他节点入度为1
    {
        if (i == root_ind)
        {
            continue;
        }
        if (in_degree[i] != 1)
        {
            return false;
        }
    }
    // 看看能不能跑通
    dfs(g, root_ind);
    for (int i = 1; i <= g.VerNum; i++)
    {
        if (visited[i] != true)
        {
            return false;
        }
    }
    return true;
}
int main()
{
    _getcwd(cwd, sizeof(cwd));
    std::string data_dir_path = std::string(cwd) + "/../src/graph/grpData/";
    std::string data_name = "dg6.grp";
    std::string data_path_str = data_dir_path + data_name;
    char* data_path = new char[data_path_str.size() + 1];
    // std::strncpy(data_path,data_path_str.c_str(),sizeof(data_path)-1);
    std::strcpy(data_path, data_path_str.c_str());
    Graph g;
    if (CreateGraphFromFile(data_path, g))
    {
        if (judge(g, 'a'))
        {
            std::cout << "有根有向";
        }
        else
        {
            std::cout << "不是";
        }
    }
    else
    {
        std::cout << "create:fail" << "\n";
    };
}
