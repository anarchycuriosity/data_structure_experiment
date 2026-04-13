#include "linked_list.h" //errorcode
#include "sqList.h"      //ErrorCode
class Stack : public linkedList
{
public:
    using linkedList::linkedList;
    errorcode get_top(int &top)
    {
        top = end->data;
        return errorcode::success;
    }

    errorcode insert(int _data)
    {
        // list_node new_node(node);
        list_node *new_node = new list_node(_data);
        list_node *tmp = end;
        end = new_node;
        end->pre = tmp;
        count++;
        return errorcode::success;
    }
    errorcode pop()
    {
        if (empty())
        {
            return errorcode::success;
        }
        list_node *tmp = end;
        end = end->pre;
        delete tmp;
        return errorcode::success;
        count--;
        return errorcode::success;
    }
};

class Queue : public linkedList_ord
{
public:
    using linkedList_ord::linkedList_ord;
    errorcode insert(int _data) // 从队尾插入
    {
        list_node *node = new list_node(_data);
        end = node;
        end->next = nullptr;
        count++;
        return errorcode::success;
    }
    errorcode pop() // 从头部弹出
    {
        list_node *del = head->next;
        head->next = head->next->next;
        delete del;
        count--;
        return errorcode::success;
    }
};
bool judge_brackets(std::string &s)
{
    Stack st;
    int top;
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == '(' || s[i] == '[' || s[i] == '{')
        {
            st.insert((int)s[i]);
        }
        else
        {
            st.get_top(top);
            if (top == '(' && s[i] == ')')
            {
                st.pop();
            }
            else if (top == '[' && s[i] == ']')
            {
                st.pop();
            }
            else if (top == '{' && s[i] == '}')
            {
                st.pop();
            }
        }
    }
    if (st.empty())
    {
        return true;
    }
    return false;
}
// pop表示已经弹出的梳理
// pop表示已经弹出的数量，ins表示已经插入的数量，如果前者大于后者则返回

// void get(Queue &q, Stack &st, int pop, int ins, int &sort_count) // queue模拟入栈，st模拟实际的栈
// {
//     if (pop > ins)
//     {
//         return;
//     }
//     if (!st.empty())
//     {
//         st.pop();
//         sort_count++;
//         get(q, st, pop + 1, ins, sort_count);
//     }
//     if (!q.empty())
//     {
//         st.insert(q.end->data);
//         q.pop();
//         sort_count++;
//         get(q, st, pop, ins + 1, sort_count);
//     }
// }
// 考虑不要维护额外的数，直接判断是不是空的就好了
void get(Queue q, Stack st, int &sort_count) // queue模拟入栈，st模拟实际的栈
{
    if (q.empty() && st.empty())
    {
        sort_count++;
        return;
    }
    if (!q.empty())
    {
        st.insert(q.end->data);
        q.pop();
        // sort_count++;
        get(q, st, sort_count);
    }
    if (!st.empty())
    {
        st.pop();
    }
}