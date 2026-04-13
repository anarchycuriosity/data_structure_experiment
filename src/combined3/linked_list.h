#ifndef LINKED_LIST_H
#define LINKED_LIST_H

// 前面的题目不需要维护count
// 但是这题因为要用回溯算法，用栈和队列模拟栈的弹出，所以需要维护个数

// linkedlist只会回收它名下的end地址，地址不管
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

// 默认的这个链表是一个倒序链表
class linkedList
{
public:
    struct list_node
    {
        int data;
        list_node *pre;
        list_node(int _data) : data(_data), pre(nullptr) {}
        list_node(int _data, list_node *_pre) : data(_data), pre(_pre) {}
    };
    // 地址随着类的消失而被回收
    list_node *end;
    int count;

public:
    // 虚拟头节点的目的是为了让每个真实节点都有前驱节点
    // end应该直接指向虚拟头，否则就根本没有追踪虚拟头，那就没有意义了
    // 在 linkedList 类内部添加
    linkedList(const linkedList &other)
    {
        if (other.end == nullptr)
        {
            this->end = nullptr;
            this->count = 0;
            return;
        }

        // 1. 复制第一个节点（在你的逆序链表中是末尾节点）
        this->end = new list_node(other.end->data);
        this->count = other.count;

        // 2. 依次遍历并复制后续节点
        list_node *dest_cur = this->end;
        list_node *src_cur = other.end->pre;

        while (src_cur != nullptr)
        {
            dest_cur->pre = new list_node(src_cur->data);
            dest_cur = dest_cur->pre;
            src_cur = src_cur->pre;
        }
    }
    linkedList()
    {
        end = nullptr;
        count = 0;
    }
    linkedList(int _data)
    {
        list_node *node = new list_node(_data);
        end = node;
        count = 1;
    }
    linkedList(const std::vector<int> &_data_vec)
    {
        list_node *cur = nullptr;
        for (int val : _data_vec)
        {
            cur->pre = new list_node(val);
            cur = cur->pre;
        }
        end = cur;
        count = _data_vec.size();
    }
    bool empty()
    {
        if (end == nullptr)
        {
            return true;
        }
        return false;
    }
    virtual ~linkedList()
    {
        // 头节点不是nullptr啊
        // 删除逻辑和别的函数不一样的，完全遍历
        list_node *cur = this->end;
        while (cur != nullptr)
        {
            /*             list_node *tmp = cur;
                        cur = cur->pre;
                        delete tmp; */

            list_node *pre_node = cur->pre;
            delete cur;
            cur = pre_node;
        }
        // 漏了虚拟头节点和最后一个节点
        // 这里改逆序链表所以不做了
        // end = nullptr;
    }
};

// 使用顺序链表进行queue的模拟
// 相比顺序链表添加一个尾部节点
class linkedList_ord
{
public:
    struct list_node
    {
        int data;
        list_node *next;
        list_node(int _data) : data(_data), next(nullptr) {}
        list_node(int _data, list_node *_next) : data(_data), next(_next) {}
    };
    list_node *head; // 这仅仅是一个地址，而不是内存
    // 地址随着类的消失而被回收
    list_node *end;
    int count;

public:
    linkedList_ord(const linkedList_ord &other)
    {
        // 1. 初始化基本的虚拟头节点
        this->head = new list_node(0);
        this->count = other.count;

        if (other.count == 0)
        {
            this->head->next = nullptr;
            this->end = nullptr;
            return;
        }

        // 2. 开始遍历并复制节点
        list_node *dest_cur = this->head;
        list_node *src_cur = other.head->next; // 跳过源链表的虚拟头

        while (src_cur != nullptr)
        {
            dest_cur->next = new list_node(src_cur->data);
            dest_cur = dest_cur->next; // 移动到新创建的节点
            src_cur = src_cur->next;
        }

        // 3. 关键：重新定位新链表的 end 指针
        // 遍历结束后，dest_cur 正好停在最后一个新创建的节点上
        this->end = dest_cur;
        this->end->next = nullptr;
    }

    // 虚拟头节点的目的是为了让每个真实节点都有前驱节点
    // head应该直接指向虚拟头，否则就根本没有追踪虚拟头，那就没有意义了
    linkedList_ord()
    {
        // 这里不应这样初始化，先让他一边晾着，反正就一个节点
        // list_node *dummy_head = new list_node(0, head);其实没什么区别
        list_node *dummy_head = new list_node(0);
        head = dummy_head;
        end = nullptr;
        head->next = end;
        count = 0;
    }
    linkedList_ord(int _data)
    {
        list_node *dummy_head = new list_node(0);
        head = dummy_head;
        list_node *node = new list_node(_data);
        head->next = node;
        end = node;
        end->next = nullptr;
        count = 1;
    }
    linkedList_ord(const std::vector<int> &_data_vec)
    {
        head = new list_node(0);
        list_node *cur = head;
        for (int val : _data_vec)
        {
            cur->next = new list_node(val);
            cur = cur->next;
        }
        end = cur;
        end->next = nullptr;
        count = _data_vec.size();
    }
    virtual ~linkedList_ord()
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
        // end指代最后的一个实体元素，会被顺便删掉
    }
    bool empty()
    {
        if (count == 0)
        {
            return true;
        }
        return false;
    }
};

#endif