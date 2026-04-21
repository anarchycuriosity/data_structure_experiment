#ifndef BTREE_H
#define BTREE_H
#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
typedef char elemenType;
struct bnode
{
      elemenType data;
      bnode *lchild, *rchild;
};
void CreateBitree(bnode *&T)
{
      char ch;
      cin >> ch;
      if (ch == '#')
            T = NULL;
      else
      {
            T = new bnode;
            T->data = ch;
            CreateBitree(T->lchild);
            CreateBitree(T->rchild);
      }
}
void Visit(bnode *t)
{
      cout << t->data;
}
void Preorder(bnode *t)
{
      if (t != NULL)
      {
            Visit(t);
            Preorder(t->lchild);
            Preorder(t->rchild);
      }
}
void Inorder(bnode *t)
{
      if (t != NULL)
      {
            Inorder(t->lchild);
            Visit(t);
            Inorder(t->rchild);
      }
}
void Postorder(bnode *t)
{
      if (t != NULL)
      {
            Postorder(t->lchild);
            Postorder(t->rchild);
            Visit(t);
      }
}
int main()
{
      bnode *T;
      CreateBitree(T);
      Preorder(T);
      cout << endl;
      Inorder(T);
      cout << endl;
      Postorder(T);
      cout << endl;
      return 0;
}
#endif