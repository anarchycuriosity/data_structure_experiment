#ifndef LINKED_LIST_H
#define LINKED_LIST_H
// linkedlist只会回收它名下的head地址，地址不管

// 其他new出来的节点需要额外删除
#include <iostream>
#include <string>
#include <vector>
#include <cstdint>
int maxlen = 250;
enum class errorcode : uint8_t // 让每个errorcode占小一点
{
    success = 0,     // 最好手动指定
    range_error = 1, // 修改链表结构的操作，索引越界,比如插入和删除，拿到元素
    not_found = 2,
    underflow = 3, // 当count为0但依然调用删除操作
    overflow = 4   // count超过模拟最大值 maxlen
};

// 总结：
// 析构函数曾经存在问题
std::string trans_code(errorcode code)
{
    switch (code)
    {
    case errorcode::success:
    {
        return "success";
    }
    case errorcode::not_found:
    {
        return "not_found";
    }
    case errorcode::range_error:
    {
        return "range_error";
    }
    case errorcode::underflow:
    {
        return "underflow";
    }
    case errorcode::overflow:
    {
        return "overflow";
    }
    }
}

class linkedList
{
private:
    struct list_node
    {
        int data;
        list_node *next;
        list_node(int _data) : data(_data), next(nullptr) {}
        list_node(int _data, list_node *_next) : data(_data), next(_next) {}
    };
    list_node *head; // 这仅仅是一个地址，而不是内存
    // 地址随着类的消失而被回收
    int count;

public:
    // 虚拟头节点的目的是为了让每个真实节点都有前驱节点
    // head应该直接指向虚拟头，否则就根本没有追踪虚拟头，那就没有意义了
    linkedList()
    {
        count = 0;
        // 这里不应这样初始化，先让他一边晾着，反正就一个节点
        // list_node *dummy_head = new list_node(0, head);其实没什么区别
        list_node *dummy_head = new list_node(0);
        head = dummy_head;
    }
    linkedList(int _data)
    {
        count = 1;
        list_node *dummy_head = new list_node(0);
        head = dummy_head;
        list_node *node = new list_node(_data);
        head->next = node;
    }
    linkedList(const std::vector<int> &_data_vec)
    {
        count = 0;
        head = new list_node(0);
        list_node *cur = head;
        for (int val : _data_vec)
        {
            cur->next = new list_node(val);
            cur = cur->next;
            count++;
        }
    }
    errorcode set_count()
    {
        list_node *cur = head;
        count = 0;
        while (cur->next != nullptr)
        {
            cur = cur->next;
            count++;
        }
        return errorcode::success;
    }
    ~linkedList()
    {
        // 头节点不是nullptr啊
        // 删除逻辑和别的函数不一样的，完全遍历
        list_node *cur = this->head;
        while (cur != nullptr)
        {
            /*             list_node *tmp = cur;
                        cur = cur->next;
                        delete tmp; */

            list_node *next_node = cur->next;
            delete cur;
            cur = next_node;
        }
        // 漏了虚拟头节点和最后一个节点
        head = nullptr;
    }
    errorcode print()
    {
        if (count == 0)
        {
            // underflow必须是非法操作
            // return errorcode::underflow;
            std::cout << "此表为空" << std::endl;
            return errorcode::success;
        }
        list_node *cur = head;
        while (cur->next != nullptr)
        {
            std::cout << cur->next->data << " ";
            cur = cur->next;
        }
        std::cout << std::endl;
        return errorcode::success;
    }

    // LOLE放奇数和偶数
    errorcode seperate_OE(linkedList &LO, linkedList &LE) // 无问题
    {
        // 让两个表的头都指向同一个是很危险的
        // 我们必须在结束的时候让this置空
        list_node *cur = this->head;
        list_node *curO = LO.head;
        list_node *curE = LE.head;
        while (cur->next != nullptr)
        {
            list_node *tmp = cur->next;
            if (tmp->data % 2 == 0)
            {
                // 曾经写错了
                curE->next = tmp;
                curE = curE->next;
                LE.count++;
            }
            else
            {
                curO->next = tmp;
                curO = curO->next;
                curO = tmp;
                LO.count++;
            }
            cur = cur->next;
        }
        // 拆掉尾巴
        curE->next = nullptr;
        curO->next = nullptr;
        // 让this置空
        this->head->next = nullptr;
        this->count = 0;
        return errorcode::success;
    }
    errorcode get_pub(linkedList &L1, linkedList &L2) // 无问题
    {
        list_node *cur1 = L1.head;
        list_node *cur2 = L2.head;
        list_node *cur3 = this->head;
        while (cur1->next != nullptr && cur2->next != nullptr)
        {
            if (cur1->next->data < cur2->next->data)
            {
                cur1 = cur1->next;
            }
            else if (cur1->next->data == cur2->next->data)
            {
                cur3->next = cur1->next; // 问题我想在这里，因为这个指针有两个归属
                cur1->next = cur1->next->next;
                cur3 = cur3->next;
                cur3->next = nullptr; // 处理让指针置空
                cur2 = cur2->next;
                this->count++;
            }
            else
            {
                cur2 = cur2->next;
            }
        }
        return errorcode::success;
    }

    // 链表断裂
    errorcode removed()
    {
        list_node *cur = this->head->next; // 从第一个有效节点开始
        if (cur == nullptr)
        {
            return errorcode::success;
        }
        // 不要引入same了，只要重复直接跳
        // int same = cur->next->data;
        while (cur->next != nullptr)
        {
            // 因为是从有效节点开始的，所以cur本身也可以用上了，而不是总是使用cur.next
            if (cur->data == cur->next->data)
            {
                list_node *to_del = cur->next;
                cur->next = cur->next->next;
                delete to_del;
                this->count--;
            }
            else
            {
                cur = cur->next;
            }
        }
        return errorcode::success;
    }
    errorcode merge(linkedList &L2)
    {
        list_node *cur1 = this->head;
        list_node *cur2 = L2.head;
        while (cur1->next != nullptr && cur2->next != nullptr)
        {
            if (cur1 != this->head && cur1->data == cur1->next->data)
            {
                list_node *to_del = cur1->next;
                cur1->next = to_del->next;
                delete to_del;
                continue;
            }

            if (cur1 != this->head && cur1->data == cur2->next->data)
            {
                list_node *to_del = cur2->next;
                cur2->next = to_del->next;
                delete to_del;
                continue;
            }

            if (cur1->next->data == cur2->next->data)
            {
                list_node *to_del = cur2->next;
                cur2->next = to_del->next;
                delete to_del;
                // 不移动L1，这个函数只做一件事情删掉2的重复节点
            }
            else if (cur1->next->data > cur2->next->data)
            {
                list_node *tmp1 = cur1->next;
                list_node *tmp2 = cur2->next->next;
                cur1->next = cur2->next;
                cur1->next->next = tmp1;
                cur1 = cur1->next; // cur1跳跃
                cur2->next = tmp2; // cur2只改next,本身不要跳
            }
            else // cur1.next.data < cur2.next.data
            {
                // 关键是我串小的，但是大的我不一定拿
                cur1 = cur1->next;
            }
        }
        // 错误1：最后两个while并无法完成合并，因为不需要遍历所以不需要while循环我傻了
        // 比较cur1和cur2->next，我脚下的路和要搭的砖
        // 观察前面的cur2，只有在相等的时候cur2才会移动，cur2本身的值是没有意义的，cur2的next才有
        // 如果不是为了接尾，其实cur1也不重要，是接尾让他变得重要了，或者说在接尾中它很重要
        // 不仅仅是去相等还要看是不是递增的！但其实前面已经帮我们做过了，剩下的肯定大，只要不重复即可
        while (cur2->next != nullptr)
        {
            if (cur1->data == cur2->next->data)
            {
                list_node *to_del = cur2->next; // 2移动，删除前一个节点
                cur2->next = to_del->next;
                delete to_del;
            }
            else
            {
                cur1->next = cur2->next;
                cur1 = cur1->next;
                cur2->next = nullptr;
                break;
            }
        }
        while (cur1->next != nullptr)
        {
            if (cur1->data == cur1->next->data)
            {
                list_node *to_del = cur1->next;
                cur1->next = cur1->next->next;
                delete to_del;
            }
            else
            {
                cur1 = cur1->next;
            }
        }

        // 多余节点都被放入L2，析构函数会把她删掉的
        // 但是如果你不把提前处理好，野指针会乱跳
        // 必须办理离职手续，在析构之前
        L2.head->next = nullptr;
        L2.count = 0;
        return errorcode::success;
    }

    // 浮动窗口
    errorcode search(int k, int &ans)
    {
        if (k < 0)
        {
            return errorcode::range_error;
        }
        list_node *fast = head;
        list_node *slow = head;
        // 使用-1来抵消后置递减
        // 但是如果链表长度是5并且k也是5的话
        //&&会导致短路，所以k并不会自减，他会是0
        /*         while (fast->next != nullptr && k--)
                {
                    fast = fast->next;
                }
                if (k != -1)
                {
                    return errorcode::range_error;
                } */

        for (int i = 0; i < k; i++)
        {
            if (fast->next == nullptr)
            {
                return errorcode::range_error;
            }
            fast = fast->next;
        }
        while (fast->next != nullptr)
        {
            fast = fast->next;
            slow = slow->next;
        }
        ans = slow->next->data;
        return errorcode::success;
    }
};

#endif