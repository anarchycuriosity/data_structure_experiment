#ifndef SQLIST_H
#define SQLIST_H
#include <vector>
#include <iostream>
enum ErrorCode
{
    success,
    overflow,
    underflow,
    rangeError
};
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
    sqList &operator=(const sqList &other)
    {
        if (this != &other) // 防止自己赋值，直接复制
        {
            this->data = other.data;
        }
        return *this;
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

    ErrorCode removed(sqList &L, int &times) // 由于是在有序的顺序表中删除，所以其实没这么复杂
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
        if (L.data.size() == 0)
        {
            return rangeError;
        }
        int fast = 1, slow = 0;
        for (; fast < L.data.size(); fast++)
        {
            if (L.data[fast] != L.data[slow]) // 不相同slow就移动，算移动一次
            {
                slow++;
                L.data[slow] = L.data[fast];
            }
        }
        times = slow;
        return success;
    }

    ErrorCode cutPrint(int start, int end) // end也会被打印，从0开始
    {
        if (end > data.size() - 1 || start < 0)
        {
            return overflow;
        }
        else if (start > end)
        {
            return rangeError;
        }
        for (int i = start; i <= end; i++)
        {
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;
        return success;
    }

    // 求并集
    sqList together(sqList &A, sqList &B)
    {
        sqList toge;
        sqList a = A;
        sqList b = B;
        int i = 0, j = 0;
        while (i < a.getLen() && j < b.getLen())
        {
            if (a.data[i] < b.data[j])
            {
                toge.push(a.data[i]);
                i++;
            }
            else if (a.data[i] == b.data[j])
            {
                toge.push(a.data[i]);
                i++;
                j++;
            }
            else
            {
                toge.push(b.data[j]);
                j++;
            }
        }
        while (i < a.getLen())
        {
            toge.push(a.data[i]);
            i++;
        }
        while (j < b.getLen())
        {
            toge.push(b.data[j]);
            j++;
        }
        return toge;
    }
    // 求交集的部分在getpub里面已经实现了
    ErrorCode minus(sqList &A, sqList &B, sqList &minus) // a - b那肯定a比b大
    {
        sqList a = A;
        sqList b = B;
        if (a.getLen() < b.getLen())
        {
            return rangeError;
        }
        int i = 0, j = 0;
        while (i < a.getLen() && j < b.getLen())
        {
            if (a.data[i] < b.data[j])
            {
                minus.push(a.data[i]); // 没匹配到就push进去，匹配到了就跳过不push
                i++;
            }
            else if (a.data[i] == b.data[j])
            {
                i++;
                j++;
            }
            else
            {
                j++;
            }
        }
        if (i < a.getLen()) // 如果a还有剩，肯定不会再被减掉了，直接全部塞回去
        {
            for (; i < a.getLen(); i++)
            {
                minus.push(a.data[i]);
            }
        }
        return success;
    }

private:
    std::vector<int> data;
};

ErrorCode findMid(sqList &L1, sqList &L2, int &mid)
{
    if (L1.getData().empty() && L2.getData().empty())
    {
        return rangeError;
    }
    // 找到中位数的位置，下标以0为标准
    int tar = ((L1.getLen() + L2.getLen()) % 2 == 0) ? (L1.getLen() + L2.getLen()) / 2 - 1 : (L1.getLen() + L2.getLen()) / 2;
    // 我们不开另一个sqlist，直接找数
    int i = 0, j = 0;
    int curInd = 0; // 遍历的指针下标
    int res = 0;    // 结果随时更新

    while (curInd <= tar)
    {
        if (i < L1.getLen() && (j >= L2.getLen() || L1.getData()[i] <= L2.getData()[j]))
        {
            res = L1.getData()[i];
            i++;
        }
        else
        {
            res = L2.getData()[j];
            j++;
        }
        curInd++;
    }
    mid = res;
    return success;
    // 双层嵌套有点容易死，因为临近点跳两个很容易出错，那就不要处理那个跳两个了，一个一个拿
    // 受到了之前合并排序表和删除重复元素的影响，必须找完其中一个才能走出来，其实完全错误了

    /*  while (curInd < tar)
     {
         // while (true)     不要这样写嵌套，不然会在仅仅最近这一两句反复横跳
         while (!(i == L1.getLen() || j == L2.getLen()))
         {
             if (L1.getData()[i] < L2.getData()[j])
             {
                 res = L1.getData()[i];
                 curInd++;
                 i++;
             }

             else if (L1.getData()[i] == L2.getData()[j])
             {
                 // curInd += 2;风险很大可能会直接跳过去
                 if (curInd + 2 > tar)
                 {
                     return res;
                 }
                 curInd += 2;
                 res = L1.getData()[i];
                 i++;
                 j++;
             }

             else
             {
                 res = L2.getData()[j];
                 curInd++;
                 j++;
             }
         }
         if (i < L1.getLen())
         {
             res = L1.getData()[i];
             curInd++;
             i++;
         }
         else if (j < L2.getLen())
         {
             res = L2.getData()[j];
             curInd++;
             j++;
         }
     }
     return res; */
}

#endif