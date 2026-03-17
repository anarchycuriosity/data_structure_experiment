#include "sqList.h"
int main()
{
    std::cout << "现在测试第一题,原数组为" << std::endl;
    std::vector<int> testList1 = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    sqList list1(testList1); // 初始化list
    list1.print();
    std::cout << "分别插入25,85,110,8" << std::endl;
    std::vector<int> testInput1 = {25, 85, 110, 8};
    for (int i = 0; i < testInput1.size(); i++)
    {
        list1.insertVal(testInput1[i]);
        list1.print();
    }

    std::cout << std::endl
              << std::endl;
    std::cout << "现在测试第二题,分别展示L1和L2的原组及其分组结果" << std::endl;
    sqList list2({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 20, 30, 40, 50, 60});
    sqList res2Odd;
    sqList res2Even;
    std::cout << "表一" << std::endl;
    list2.print();
    list2.seperate(res2Odd, res2Even);
    res2Odd.print();
    res2Even.print();
    std::cout << std::endl;
    std::cout << "表二" << std::endl;
    sqList list3({10, 20, 30, 40, 50, 60, 70, 80, 90, 100});
    sqList res3Odd;
    sqList res3Even;
    list3.print();
    list3.seperate(res3Odd, res3Even);
    res3Odd.print();
    res3Even.print();

    std::cout << std::endl
              << std::endl;
    std::cout << "现在测试第三题,每次将下面两行顺序表合并" << std::endl;
    std::vector<std::vector<int>> testVec1s = {{1, 3, 6, 10, 15, 16, 17, 18, 19, 20}, {1, 3, 6, 10, 15, 16, 17, 18, 19, 20}, {}};
    std::vector<std::vector<int>> testvec2s = {{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 18, 20, 30}, {2, 4, 5, 7, 8, 9, 12, 22}, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}};
    for (int i = 0; i < 3; i++)
    {
        std::cout << "第" << i + 1 << "组" << std::endl;
        sqList L1(testVec1s[i]);
        sqList L2(testvec2s[i]);
        L1.print();
        L2.print();
        sqList list3 = list3.findPub(L1, L2);
        list3.print();
    }

    std::cout << std::endl
              << std::endl;
    std::cout << "现在测试第四题,每次展示原表和删除后的表" << std::endl;
    std::vector<std::vector<int>> testVec3s = {{1, 2, 3, 4, 5, 6, 7, 8, 9},
                                               {1, 1, 2, 2, 2, 3, 4, 5, 5, 5, 6, 6, 7, 7, 8, 8, 9},
                                               {1, 2, 3, 4, 5, 5, 6, 7, 8, 8, 9, 9, 9, 9, 9}};

    for (int i = 0; i < 3; i++)
    {
        sqList list4(testVec3s[i]);
        list4.print();
        int count = list4.removed(list4);
        std::cout << count << std::endl;
        // list4.cutPrint(0, list4.removed(list4));这会调用多次removed函数
        list4.cutPrint(0, count);
        std::cout
            << std::endl;
    }

    sqList tmp1({1, 3}), tmp2({2, 3});
    std::cout << findMid(tmp1, tmp2);
}