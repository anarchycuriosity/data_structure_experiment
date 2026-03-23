#ifndef LINKED_LIST_H
#define LINKED_LIST_H
// linkedlist只会回收它名下的head地址，地址不管
// 其他new出来的节点需要额外删除
#include <iostream>
#include <string>
#include <vector>
int maxlen = 250;
enum class errorcode : uint8_t // 让每个errorcode占小一点
{
    success = 0,     // 最好手动指定
    range_error = 1, // 修改链表结构的操作，索引越界,比如插入和删除，拿到元素
    not_found = 2,
    underflow = 3, // 当count为0但依然调用删除操作
    overflow = 4   // count超过模拟最大值 maxlen
};

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

    ~linkedList()
    {
        list_node *cur = this->head;
        while (cur->next != nullptr)
        {
            /*             list_node *tmp = cur;
                        cur = cur->next;
                        delete tmp; */

            list_node *next_node = cur->next;
            delete cur;
            cur = next_node;
        }
        // 漏了虚拟头节点和最后一个节点
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
        list_node *cur = this->head;
        list_node *curO = LO.head;
        list_node *curE = LE.head;
        while (cur->next != nullptr)
        {
            list_node *tmp = cur->next;
            if (tmp->data % 2 == 0)
            {
                curE = tmp;

                LE.count++;
            }
            else
            {
                curO = tmp;
                LO.count++;
            }
            cur = cur->next;
        }
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
                cur3->next = cur1->next;
                cur1 = cur1->next;
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
    errorcode removed() // 不会出问题
    {
        list_node *cur = this->head;
        int same = cur->next->data;
        while (cur->next != nullptr)
        {
            if (cur->next->data == same)
            {
                list_node *toDel = cur->next;
                cur->next = cur->next->next;
                delete toDel;
            }
            else
            {
                same = cur->next->data;
            }
            cur = cur->next;
        }
        return errorcode::success;
    }
    errorcode merge(linkedList &L2)
    {
        list_node *cur1 = this->head;
        list_node *cur2 = L2.head;
        while (cur1->next != nullptr && cur2->next != nullptr)
        {
            if (cur1->next->data == cur2->next->data)
            {
                cur1 = cur1->next;
                cur2 = cur2->next;
            }
            else if (cur1->next->data > cur2->next->data)
            {
                list_node *tmp = cur2->next->next;
                cur2->next->next = cur1->next;
                cur1->next = cur2->next;
                cur1 = cur1->next;

                cur2->next = tmp;
                cur2 = cur2->next;
            }
            else
            {
                list_node *tmp = cur2->next->next;
                cur2->next->next = cur1->next->next;
                cur1->next->next = cur2->next;
                cur1 = cur1->next;

                cur2->next = tmp;
                cur2 = cur2->next;
            }
        }
        while (cur2->next != nullptr)
        {
            cur1->next = cur2->next;
        }
        // 多余节点都被放入L2，析构函数会把她删掉的
        return errorcode::success;
    }
};

#endif