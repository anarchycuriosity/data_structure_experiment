#ifndef SQLIST_H
#define SQLIST_H
#include <vector>
#include <iostream>
class sqList
{
public:
    sqList(const std::vector<int> &_data)
    {
        for (int i = 0; i < _data.size(); i++)
        {
            data.push_back(_data[i]);
        }
    }
    sqList()
    {
    }
    int getLen()
    {
        return data.size();
    }
    void insertVal(int val) // 按值插入，保持原递增有序
    {
        data.push_back(0);
        int tar = data.size() - 1; // tar代表要插入的位置
        for (int i = 0; i < data.size(); i++)
        {
            if (val <= data[i])
            {
                tar = i;
                break;
            }
        }
        if (tar == data.size() - 1) // 仅仅是上面的函数无法插入最大值
        {
            data[data.size() - 1] = val;
            return;
        }
        for (int j = data.size() - 1; j >= tar + 1; j--)
        {
            data[j] = data[j - 1];
        }
        data[tar] = val;
    }
    void print()
    {
        // 如果类中啥都没有就打个回车然后退出
        if (data.size() == 0)
        {
            std::cout << "没有元素" << std::endl;
            return;
        }
        for (int i = 0; i < data.size(); i++)
        {
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;
    }

    void push(int val) // 用于插入元素
    {
        data.push_back(val);
    }
    void seperate(sqList &resOdd, sqList &resEven) // 将结果数据分别存于两个数组
    {
        for (int i = 0; i < data.size(); i++)
        {
            if (data[i] % 2 != 0)
            {
                resOdd.push(data[i]);
            }
            else
            {
                resEven.push(data[i]);
            }
        }
    }
    std::vector<int> getData()
    {
        return data;
    }

    sqList findPub(sqList &L1, sqList &L2)
    {
        sqList res; // 求交集
        std::vector<int> v1 = L1.data;
        std::vector<int> v2 = L2.data;
        if (v1.size() == 0 || v2.size() == 0)
        {
            return res;
        }
        int i = 0, j = 0;
        while (true)
        {
            if (i == v1.size() || j == v2.size())
            {
                break;
            }
            if (v1[i] == v2[j])
            {
                res.push(v1[i]);
                i++;
                j++;
                break;
            }
            else if (v1[i] < v2[j])
            {
                i++;
            }
            else
            {
                j++;
            }
        }
        return res;
    }
    sqList mergeList(sqList &L1, sqList &L2) // 递增特点，考虑双指针而不是暴力检索，同时不需要使用set
    {                                        // 由于需要从两个表里面选元素插入，所以利用前面的insert似乎不是那么合适
        sqList res;                          // 求交集
        std::vector<int> &v1 = L1.data;      // 弄个引用不然拷贝太多
        std::vector<int> &v2 = L2.data;
        if (v1.size() == 0 || v2.size() == 0)
        {
            return res;
        }
        int i = 0, j = 0;
        while (true)
        {
            if (i == v1.size() || j == v2.size())
            {
                break;
            }
            if (v1[i] == v2[j])
            {
                res.push(v1[i]);
                i++;
                j++;
            }
            else if (v1[i] < v2[j])
            {
                res.push(v1[i]);
                i++;
            }
            else
            {
                res.push(v2[j]);
                j++;
            }
        }
        return res;
    }

    int removed(sqList &L) // 由于是在有序的顺序表中删除，所以其实没这么复杂
    {
        /*
        int count = 0; // 不太懂我这种方法应该怎么算
        int len = L.data.size();
        std::vector<int> res;
        res.push_back(L.data[0]);
        int j = 0;
        for (int i = 1; i < L.data.size(); i++)
        {
            if (L.data[i] != res[j])
            {
                res.push_back(L.data[i]);
                j++;
            }
        }
        L.data = res;
        */
        // 采用快慢指针
        int ind;
        int fast = 1, slow = 0;
        for (; fast < L.data.size(); fast++)
        {
            if (L.data[fast] != L.data[slow]) // 不相同slow就移动，算移动一次
            {
                slow++;
                L.data[slow] = L.data[fast];
            }
        }
        return slow;
    }

    void cutPrint(int start, int end) // end也会被打印，从0开始
    {
        for (int i = start; i <= end; i++)
        {
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;
    }

private:
    std::vector<int> data;
};
#endif