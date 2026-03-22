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
        std::cout << std::endl;
        sqList list4(testVec3s[i]);
        list4.print();
        int count = 0;
        list4.removed(list4, count);
        if (list4.removed(list4, count) == success)
        {
            std::cout << "success" << " " << count << std::endl;
            // list4.cutPrint(0, list4.removed(list4));这会调用多次removed函数
            if (list4.cutPrint(0, count) == success)
            {
                // if已经执行，所以不能再写否则打印2次
                //  list4.cutPrint(0, count);
            }
            else
            {
                std::cout << "overflow，不打印" << std::endl;
            }
        }
        else
        {
            std::cout << "rangeError" << std::endl;
        }
    }

    // 测试并集
    std::cout << std::endl
              << std::endl;
    std::cout << "现在测试并集, 每次将下面两行顺序表合并" << std::endl;
    std::vector<std::vector<int>> union_vec1 = {{1, 3, 6, 10, 15}, {1, 3, 6}, {}};
    std::vector<std::vector<int>> union_vec2 = {{1, 2, 3, 4, 5, 6}, {2, 4, 5}, {1, 2, 3}};

    for (int i = 0; i < 3; i++)
    {
        std::cout << "第" << i + 1 << "组" << std::endl;
        sqList L1(union_vec1[i]);
        sqList L2(union_vec2[i]);
        L1.print();
        L2.print();

        sqList res_u;
        res_u = res_u.together(L1, L2);
        std::cout << "并集结果: ";
        res_u.print();

        std::cout << "测试自操作a = a op b" << std::endl;
        L1 = L1.together(L1, L2);
        std::cout << "并集结果: ";
        res_u.print();
    }

    // 测试交集
    std::cout << std::endl
              << std::endl;
    std::cout << "现在测试交集, 寻找两行顺序表的公共元素" << std::endl; // 如果是0就打印空，所以不用errorcode
    std::vector<std::vector<int>> pub_vec1 = {{1, 3, 6, 10, 15}, {1, 2, 3}, {10, 20}};
    std::vector<std::vector<int>> pub_vec2 = {{3, 6, 11, 15}, {4, 5, 6}, {10, 20}};

    for (int i = 0; i < 3; i++)
    {
        std::cout << "第" << i + 1 << "组" << std::endl;
        sqList L1(pub_vec1[i]);
        sqList L2(pub_vec2[i]);
        L1.print();
        L2.print();

        sqList res_p;
        res_p = res_p.findPub(L1, L2);
        std::cout << "交集结果: ";
        res_p.print();

        std::cout << "测试自操作结果a = a op b" << std::endl;
        {
            L1 = L1.findPub(L1, L2);
            std::cout << "交集结果: ";
            L1.print();
        }
    }

    // 测试差集
    std::cout << std::endl
              << std::endl;
    std::cout << "现在测试差集，计算 L1 - L2 的结果" << std::endl;
    std::vector<std::vector<int>> minus_vec1 = {{1, 2, 3, 4, 5, 6}, {10, 20, 30}, {1, 3, 5}};
    std::vector<std::vector<int>> minus_vec2 = {{2, 4, 6}, {5, 10, 15}, {1, 3, 5}};

    for (int i = 0; i < 3; i++)
    {
        std::cout << "第" << i + 1 << "组" << std::endl;
        sqList L1(minus_vec1[i]);
        sqList L2(minus_vec2[i]);
        L1.print();
        L2.print();

        sqList res_m;
        if (res_m.minus(L1, L2, res_m) == success)
        {
            std::cout << "差集结果: ";
            res_m.print();
        }
        else
        {
            std::cout << "计算差集失败 " << std::endl;
        }

        std::cout << "测试自操作a = a op b" << std::endl;
        if (L1.minus(L1, L2, L1) == success)
        {
            std::cout << "结果: ";
            L1.print();
        }
        else
        {
            std::cout << "计算失败 " << std::endl;
        }
    }

    std::cout << "现在测试求中位数,展示原表和中位数" << std::endl;
    sqList tmp0, tmp00;
    int mid = 0;
    if (findMid(tmp0, tmp00, mid) == success)
    {
        tmp0.print();
        tmp00.print();
        std::cout << mid;
    }
    else
    {
        std::cout << "underflow，不展示任何" << std::endl;
    }

    sqList tmp1({1, 3}), tmp2({2, 3});
    if (findMid(tmp1, tmp2, mid) == success)
    {
        tmp1.print();
        tmp2.print();
        std::cout << mid;
    }
    else
    {
        std::cout << "underflow,不展示任何" << std::endl;
    };
}