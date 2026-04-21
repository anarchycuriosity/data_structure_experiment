#include "CreateBiTree.h"
#include "createtree.h"
#include <map>
#include <vector>
void s1_convert_array(bnode *root, elemen_type *s1) // s1数组从1开始存
{
    int i = 1;
    std::queue<bnode *> q;
    q.push(root);
    while (root != nullptr)
    {
        bnode *node = q.front();
        s1[i] = node->data;
        if (node->lchild)
        {
            s1[2 * i] = node->lchild->data;
            q.push(node->lchild);
        }
        else
        {
            s1[2 * i] = (elemen_type)'#';
        }
        if (node->rchild)
        {
            s1[2 * i + 1] = node->rchild->data;
            q.push(node->rchild);
        }
        else
        {
            s1[2 * i + 1] = (elemen_type)'#';
        }
        i++;
    }
}
void print(elemen_type *arr)
{
    for (int i = 1;; i++)
    {
        if (arr[i] == '\0')
        {
            break;
        }
        std::cout << arr[i] << " ";
    }
}

void s2_find_relation(bnode *root, std::map<std::string, elemen_type> relations, elemen_type tar)
{
    elemen_type s1[NODE_NUM + 1];
    s1_convert_array(root, s1);
    for (int i = 1; i <= NODE_NUM; i++)
    {
        if (s1[i] == tar)
        {
            if (i % 2 == 0)
            {
                int father_ind = i / 2;
                if (s1[father_ind])
                {
                    relations.insert({"father", s1[father_ind]});
                }
                else
                {
                    relations.insert({"father", (elemen_type)'#'});
                }

                int right_bro_ind = i + 1;
                if (right_bro_ind <= NODE_NUM)
                {
                    if (s1[right_bro_ind])
                    {
                        relations.insert({"right_bro", s1[right_bro_ind]});
                    }
                    else
                    {
                        relations.insert({"right_bro", (elemen_type)'#'});
                    }
                }

                int lchild_ind = 2 * i;
                if (lchild_ind <= NODE_NUM)
                {
                    if (s1[lchild_ind])
                    {
                        relations.insert({"left_child", s1[lchild_ind]});
                    }
                    else
                    {
                        relations.insert({"left_child", (elemen_type)'#'});
                    }
                }

                int rchild_ind = 2 * i + 1;
                if (rchild_ind <= NODE_NUM)
                {
                    if (s1[rchild_ind])
                    {
                        relations.insert({"right_child", s1[rchild_ind]});
                    }
                    else
                    {
                        relations.insert({"right_child", (elemen_type)'#'});
                    }
                }
            }
            else
            {
                int father_ind = i / 2;
                if (s1[father_ind])
                {
                    relations.insert({"father", s1[father_ind]});
                }
                else
                {
                    relations.insert({"father", (elemen_type)'#'});
                }

                int left_bro_ind = i - 1;
                if (left_bro_ind <= NODE_NUM)
                {
                    if (s1[left_bro_ind])
                    {
                        relations.insert({"left_bro", s1[left_bro_ind]});
                    }
                    else
                    {
                        relations.insert({"left_bro", (elemen_type)'#'});
                    }
                }

                int lchild_ind = 2 * i;
                if (lchild_ind <= NODE_NUM)
                {
                    if (s1[lchild_ind])
                    {
                        relations.insert({"left_child", s1[lchild_ind]});
                    }
                    else
                    {
                        relations.insert({"left_child", (elemen_type)'#'});
                    }
                }

                int rchild_ind = 2 * i + 1;
                if (rchild_ind <= NODE_NUM)
                {
                    if (s1[rchild_ind])
                    {
                        relations.insert({"right_child", s1[rchild_ind]});
                    }
                    else
                    {
                        relations.insert({"right_child", (elemen_type)'#'});
                    }
                }
            }
        }
    }
}

// 因为要找祖先，所以我们用后序搜索，找到直接就返回
// 递归不需要借助数据结构
bnode *s3_find_lca(bnode *root, elemen_type l, elemen_type r) // local_common_ancestor
{
    if (root == nullptr || root->data == l || root->data == r)
    {
        return root;
    }

    bnode *left = s3_find_lca(root->lchild, l, r);
    bnode *right = s3_find_lca(root->rchild, l, r);
    if (left != nullptr && right != nullptr)
    {
        return root; // 如果真的找到了，这里就是第一层递归，return直接结束了
    }
    // 但万一已经到了第一层递归，但是右边还是没找到东西，因为东西都在左边
    // 必须要返回，不然就没有返回值了
    return (left != nullptr) ? (left) : (right);
}
void s4_find_leaf_path(bnode *root, std::vector<elemen_type> &path) // 找到叶子节点的路径并输出
{
    if (root == nullptr)
    {
        return; // 此时的root不是叶子，它啥也不是
    }
    path.push_back(root->data);
    if (root->lchild == nullptr && root->rchild == nullptr)
    {
        std::cout << root->data << " : ";
        for (int i = path.size() - 1; i >= 0; i--)
        {
            std::cout << path[i] << " -> ";
        }
        std::cout << "\n";
    }
    else
    {
        s4_find_leaf_path(root->lchild, path);
        s4_find_leaf_path(root->rchild, path);
    }
    path.pop_back();
    // 这个弹出非常的有讲究
    // 当第一层深入递归之后，它所在的栈帧会暂停，递归回来，这个弹出才会被执行，我甚至一开始愚蠢的以为它不会被执行
    // 并不是只有写了return这层才会结束，return只是人为设计的为了提前返回，防止对空指针重复操作，和设计返回任务罢了
}