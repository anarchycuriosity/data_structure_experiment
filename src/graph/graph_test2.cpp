// #include "createGrpAdjLinkedList.h"
#include <crtdbg.h>
#include <direct.h>

#include <iostream>
#include <stack>
#include <string>
#include <vector>

#include "createGrpAdjMatrix.h"
char cwd[1024];
const int max_size = 100;
bool visited[max_size];  // 放全局默认为false
// 基于节点，而不是边，所以用一维数组而不是二维
// UDG不加visited不仅仅是性能差的问题了，而是永远跑不完，因为会无尽地被拉回去，如果又abba这种数据
bool path_e(Graph g, elementType start, elementType end) {
    // 应该是基于顶点进行深搜，而不是pair
    //  // 深搜
    //  std::pair<cellType, cellType> edge;
    //  std::stack<std::pair<cellType, cellType>> st;
    std::stack<cellType> st;
    // 找到数据对应的序号
    cellType start_ind = 1;
    cellType end_ind = 1;
    for (int i = 1; i <= 26; i++) {
        if (g.Data[i] == start) {
            start_ind = i;
        }
        if (g.Data[i] == end) {
            end_ind = i;
        }
    }
    // 一定要记得先初始化栈，先压点什么东西
    st.push(start_ind);
    while (!st.empty()) {
        cellType curr = st.top();
        st.pop();
        if (visited[curr] == true) {
            continue;
        }
        visited[curr] = true;
        if (curr == end_ind) {
            return true;
        }
        for (int next = 1; next <= 26; next++) {
            if (g.AdjMatrix[curr][next] == true &&
                visited[next] == false)  // 判断可以去到下一个节点并且下一个节点没有被推入栈过
            {
                st.push(next);
            }
        }
    }
    return false;
    // while (!st.empty())
    // {
    //     edge = st.top();
    //     st.pop();
    //     if(visited[edge.first][edge.second] == false)
    //     {
    //         if (st.top().second == end_ind)
    //         {
    //             return true;
    //         }
    //         for (int ind2 = 1; ind2 <= 26; ind2++)
    //         {
    //             if (g.AdjMatrix[ind1][ind2] == true)
    //             {
    //                 st.push({ind1, ind2});
    //             }
    //         }
    //     }
    //     visited[edge.first][edge.second] = true;
    //     ind1 = edge.second;
    // }
    // return false;
}

int main() {
    _getcwd(cwd, sizeof(cwd));
    std::string data_dir_path = std::string(cwd) + "/../src/graph/grpData/";
    std::string data_name = "udg8.grp";
    std::string data_path_str = data_dir_path + data_name;
    char* data_path = new char[data_path_str.size() + 1];
    // std::strncpy(data_path,data_path_str.c_str(),sizeof(data_path)-1);
    std::strcpy(data_path, data_path_str.c_str());
    Graph g;
    if (CreateGrpFromFile(data_path, g)) {
        elementType start = 'a';
        elementType end = 'b';
        if (path_e(g, start, end)) {
            std::cout << "path exists";
        } else {
            std::cout << "no way";
        }
    } else {
        std::cout << "create:fail" << "\n";
    };
}
