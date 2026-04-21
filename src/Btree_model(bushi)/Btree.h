#ifndef BTREE_H
#define BTREE_H

#include <iostream>
#include <cstdio>
#include <cstring>
// 创建二叉树
void create_bitree(struct bnode *&t);
// 访问结点
void visit(struct bnode *t);
// 先序遍历
void preorder(struct bnode *t);
// 中序遍历
void inorder(struct bnode *t);
// 后序遍历
void postorder(struct bnode *t);
typedef char elemen_type;

struct bnode
{
      elemen_type data;
      bnode *lchild;
      bnode *rchild;
};

void create_bitree(bnode *&t)
{
      char ch;
      std::cin >> ch;
      if (ch == '#')
      {
            t = NULL;
      }
      else
      {
            t = new bnode;
            t->data = ch;
            create_bitree(t->lchild);
            create_bitree(t->rchild);
      }
}

void visit(bnode *t)
{
      std::cout << t->data;
}

void preorder(bnode *t)
{
      if (t != NULL)
      {
            visit(t);
            preorder(t->lchild);
            preorder(t->rchild);
      }
}

void inorder(bnode *t)
{
      if (t != NULL)
      {
            inorder(t->lchild);
            visit(t);
            inorder(t->rchild);
      }
}

void postorder(bnode *t)
{
      if (t != NULL)
      {
            postorder(t->lchild);
            postorder(t->rchild);
            visit(t);
      }
}

// 警告：头文件中绝对不要写 main 函数！我已经帮你注释掉了，你应该把它移到单独的 .cpp 文件中。
/*
int main()
{
    bnode *t;
    create_bitree(t);
    preorder(t);
    std::cout << std::endl;
    inorder(t);
    std::cout << std::endl;
    postorder(t);
    std::cout << std::endl;
    return 0;
}
*/

#endif