#include "linked_list.h"

int main()
{
    // --- 第一题：奇偶分解 ---
    std::cout << "现在测试第一题, 分解奇偶项" << std::endl;
    std::vector<std::vector<int>> test_vec_1 = {
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 20, 30, 40, 50, 60},
        {10, 20, 30, 40, 50, 60, 70, 80, 90, 100}};

    for (int i = 0; i < test_vec_1.size(); i++)
    {
        std::cout << "第" << i + 1 << "组原表: ";
        linkedList L1(test_vec_1[i]);
        L1.print();

        linkedList LO, LE;
        L1.seperate_OE(LO, LE);

        std::cout << "奇数链表: ";
        LO.print();
        std::cout << "偶数链表: ";
        LE.print();
        std::cout << std::endl;
    }

    // --- 第二题：求公共元素 ---
    std::cout << "现在测试第二题, 求两个递增链表的公共元素" << std::endl;
    std::vector<std::vector<int>> pub_l1 = {
        {1, 2, 2, 3, 15, 16, 17, 18, 19, 20},
        {3, 4, 4, 5, 15, 16, 17, 18, 19, 20},
        {}};
    std::vector<std::vector<int>> pub_l2 = {
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 18, 20, 30},
        {2, 4, 5, 7, 8, 9, 12, 22},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}};

    for (int i = 0; i < 3; i++)
    {
        std::cout << "第" << i + 1 << "组" << std::endl;
        linkedList L1(pub_l1[i]);
        linkedList L2(pub_l2[i]);
        linkedList L3;

        L1.print();
        L2.print();
        L3.get_pub(L1, L2);
        std::cout << "公共元素(L3): ";
        L3.print();
        std::cout << std::endl;
    }

    // --- 第三题：删除重复元素 ---
    std::cout << "现在测试第三题, 删除递增有序表中的重复元素" << std::endl;
    std::vector<std::vector<int>> dup_vecs = {
        {1, 2, 3, 4, 5, 6, 7, 8, 9},
        {1, 1, 2, 2, 2, 3, 4, 5, 5, 5, 6, 6, 7, 7, 8, 8, 9},
        {1, 2, 3, 4, 5, 5, 6, 7, 8, 8, 9, 9, 9, 9, 9}};

    for (int i = 0; i < 3; i++)
    {
        linkedList L(dup_vecs[i]);
        std::cout << "原表: ";
        L.print();
        L.removed();
        std::cout << "去重后: ";
        L.print();
        std::cout << std::endl;
    }

    // --- 第四题：合并集合 ---
    std::cout << "现在测试第四题, 利用原表结点合并集合 (L1 = L1 合并 L2)" << std::endl;
    for (int i = 0; i < 3; i++)
    {
        std::cout << "第" << i + 1 << "组" << std::endl;
        linkedList L1(pub_l1[i]); // 复用第二题的数据
        linkedList L2(pub_l2[i]);
        L1.print();
        L2.print();

        L1.merge(L2);
        std::cout << "合并结果: ";
        L1.print();
        std::cout << std::endl;
    }

    // --- 第五题：查找倒数第K个 ---
    std::cout << "现在测试第五题, 查找倒数第K个结点" << std::endl;
    linkedList L_final({1, 2, 3, 4, 5});
    int k = 2;
    int ans = 0;
    std::cout << "链表内容: ";
    L_final.print();
    if (L_final.search(k, ans) == errorcode::success)
    {
        std::cout << "倒数第 " << k << " 个元素的值为: " << ans << std::endl;
    }
    else
    {
        std::cout << "查找失败, 索引可能越界" << std::endl;
    }

    return 0;
}