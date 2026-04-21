#ifndef CREATE_BI_TREE_H
#define CREATE_BI_TREE_H

#include "Btree.h"
#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue> // 引入标准库队列以替代你原本的临时队列

#define NODE_NUM 100 // 定义最大结点数
// 层次遍历
void hie_traverse(struct bnode *t);
// 递归创建子树
void create_sub_tree(struct bnode *&p, int k);
// 主控创建函数 (交互式)
void create_bt_console(struct bnode *&t);
// 获取完全二叉树数组
void get_complete_arr(char *arr, int &num);
// 创建完全二叉树
void create_bt_arr(struct bnode *&t, char *in_arr, int i, int n);
// 从文件读取到数组
bool read_file_to_array(char file_name[], char str_line[100][3], int &n_arr_len);
// 从数组创建树
bool create_bi_tree_from_file(struct bnode *&p_bt, char str_line[100][3], int n_len, int &n_row);
// 删除字符串左边空格
void str_l_trim(char *str);
void str_l_trim(char *str); // 申明删除字符串左边空格

// 层次遍历--因为结构定义及运算实现的次序关系，临时放在此处
void hie_traverse(bnode *t)
{
	if (t == NULL)
	{
		return;
	}

	std::queue<bnode *> q;
	q.push(t);

	while (!q.empty())
	{
		bnode *p = q.front();
		std::cout << p->data << " "; // 访问根结点。打印当前结点元素值，替代visit(T)函数
		q.pop();

		if (p->lchild)
		{
			q.push(p->lchild);
		}
		if (p->rchild)
		{
			q.push(p->rchild);
		}
	}
}

// 键盘交互创建二叉树开始-------------------------------------------------------------------------
// 键盘交互递归创建二叉树子树函数
void create_sub_tree(bnode *&p, int k)
{
	// k=1--左子树；k=2--右子树
	bnode *s;
	elemen_type x;
	std::cout << "请输入结点元素数值，'/'表示无子树，x=";
	std::cin >> x;

	if (x != '/')
	{
		s = new bnode;
		s->data = x;
		s->lchild = NULL;
		s->rchild = NULL;

		if (k == 1)
		{
			p->lchild = s; // s接到p的左孩子
		}
		if (k == 2)
		{
			p->rchild = s; // s接为p的右孩子
		}
		create_sub_tree(s, 1); // 递归创建s的左子树
		create_sub_tree(s, 2); // 递归创建s的右子树
	}
}

// 键盘交互创建二叉树主控函数
void create_bt_console(bnode *&t)
{
	elemen_type x;
	std::cout << "请按先序序列输入二叉树结点，（‘/’表示无子树）:" << std::endl;
	std::cout << "请输入结点元素数值，'/'表示无子树，x=";
	std::cin >> x;

	if (x == '/')
	{
		return; // 空树，退出
	}

	t = new bnode;
	t->data = x;
	t->lchild = NULL;
	t->rchild = NULL;

	create_sub_tree(t, 1); // 创建根结点的左子树
	create_sub_tree(t, 2); // 创建根结点的右子树
}
// 键盘交互创建二叉树开始-------------------------------------------------------------------------

// 键盘交互完全二叉树方式创建二叉树开始-------------------------------------------------------------------------
void get_complete_arr(elemen_type *arr, int &num)
{
	// 完全二叉树顺序存储方式创建二叉链表结构二叉树
	// 缺少的结点数值用'/'代替
	// 用'#'结束结点输入
	// arr为结点数组
	// num返回实际结点数
	elemen_type x;
	int i = 1; // arr[0]单元不用
	num = 0;

	std::cout << "请按完全二叉树方式输入二叉树结点，‘/’表示缺少结点，'#'结束输入。" << std::endl;
	std::cout << "请输入结点元素数值，'/'表示缺少结点，'#'结束输入，x=";
	std::cin >> x;

	while (x != '#')
	{
		*(arr + i) = x;
		i++;
		num++;
		std::cin >> x;
	}
}

void create_bt_arr(bnode *&t, elemen_type *in_arr, int i, int n)
{
	// t--为根结点指针
	// in_arr--为按完全二叉树存储的树的结点数组
	// i--当前结点序号
	// n--二叉树结点总数
	if (i > n)
	{
		return;
	}

	if (in_arr[i] != '/') // 有效数据创建结点
	{
		t = new bnode;		 // 创建根结点
		t->data = in_arr[i]; // 结点赋值
		t->lchild = NULL;
		t->rchild = NULL;
	}

	create_bt_arr(t->lchild, in_arr, 2 * i, n);		// 递归创建T的左子树
	create_bt_arr(t->rchild, in_arr, 2 * i + 1, n); // 递归创建T的右子树
}

// 键盘交互完全二叉树方式创建二叉树结束-------------------------------------------------------------------------

// 数据文件创建二叉树开始-------------------------------------------------------------------------
//********************** 从数据文件创建二叉树 ***********************//
//* 分两步完成：第一步将数据从文本文件读入数组                      *//
//* 第二步从数组递归创建二叉树                                      *//
//* 两步由2个函数完成                                               *//
//*******************************************************************//

// 从文本文件数据读入到数组中，同时返回实际结点数量
bool read_file_to_array(char file_name[], char str_line[NODE_NUM][3], int &n_arr_len)
{
	// 读文本文件数据到数组，返回数组及其长度
	FILE *p_file;	   // 定义二叉树的文件指针
	char str[1000];	   // 存放读出一行文本的字符串
	char str_temp[10]; // 判断是否注释行

	p_file = fopen(file_name, "r");
	if (!p_file)
	{
		std::cout << "错误：文件" << file_name << "打开失败。" << std::endl;
		return false;
	}

	while (fgets(str, 1000, p_file) != NULL) // 跳过空行和注释行
	{
		// 删除字符串左边空格
		str_l_trim(str);
		if (str[0] == '\n') // 空行，继续读取下一行
		{
			continue;
		}

		strncpy(str_temp, str, 2);
		if (strstr(str_temp, "//") != NULL) // 跳过注释行
		{
			continue;
		}
		else // 非注释行、非空行，跳出循环
		{
			break;
		}
	}

	// 循环结束，str中应该已经是二叉树数据标识"BinaryTree"，判断文件格式
	if (strstr(str, "BinaryTree") == NULL)
	{
		printf("错误：打开的文件格式错误！\n");
		fclose(p_file); // 关闭文件
		return false;
	}

	n_arr_len = 0; // 数组行号初始化为0
	while (fgets(str, 1000, p_file) != NULL)
	{
		// 删除字符串左边空格
		str_l_trim(str);
		if (str[0] == '\n') // 空行，继续读取下一行
		{
			continue;
		}

		strncpy(str_temp, str, 2);
		if (strstr(str_temp, "//") != NULL) // 注释行，跳过，继续读取下一行
		{
			continue;
		}

		char *token = strtok(str, " "); // 以空格为分隔符，分割一行数据
		if (token == NULL)				// 分割为空串，失败退出
		{
			printf("错误：读取二叉树结点数据失败！\n");
			fclose(p_file); // 关闭文件
			return false;
		}

		str_line[n_arr_len][0] = *token; // 获取结点数据
		token = strtok(NULL, " ");		 // 读取下一个子串，即此结点的左子树信息
		if (token == NULL)				 // 分割为空串，失败退出
		{
			printf("错误：读取二叉树结点数据失败！\n");
			fclose(p_file); // 关闭文件
			return false;
		}
		str_line[n_arr_len][1] = *token; // 获取此结点的左子树信息数据
		token = strtok(NULL, " ");		 // 读取下一个子串，即此结点的右子树信息
		if (token == NULL)				 // 分割为空串，失败退出
		{
			printf("错误：读取二叉树结点数据失败！\n");
			fclose(p_file); // 关闭文件
			return false;
		}
		str_line[n_arr_len][2] = *token; // 获取此结点的右子树信息数据

		n_arr_len++; // 数组行号加1
	}

	fclose(p_file); // 关闭文件
	return true;
}

// 从数组创建二叉树--数组中保存的是二叉树的先序序列，及每个结点的子树信息
bool create_bi_tree_from_file(bnode *&p_bt, char str_line[NODE_NUM][3], int n_len, int &n_row)
{
	// str_line[NODE_NUM][3]--保存节点数据的二维数组
	// n_len--数组长度，即：节点个数
	// n_row--数组当前行号

	if ((n_row >= n_len) || (n_len == 0))
	{
		return false; // 数据已经处理完毕，或者没有数据，退出
	}

	// 根据数组数据递归创建子树
	p_bt = new bnode;
	p_bt->data = str_line[n_row][0];
	p_bt->lchild = NULL;
	p_bt->rchild = NULL;

	int n_row_next = n_row; // 保留本次递归的行号

	if (str_line[n_row_next][1] == '1') // 当前结点有左子树，递归创建左子树，读下一行数据
	{
		n_row++;
		create_bi_tree_from_file(p_bt->lchild, str_line, n_len, n_row);
	}

	if (str_line[n_row_next][2] == '1') // 当前结点有右子树，递归创建右子树，读下一行数组
	{
		n_row++;
		create_bi_tree_from_file(p_bt->rchild, str_line, n_len, n_row);
	}

	return true;
}

// 数据文件创建二叉树结束------------------------------------------------------------------------

// 删除字符串、字符数组左边空格
void str_l_trim(char *str)
{
	int i, j;
	int n = 0;
	n = strlen(str) + 1;
	for (i = 0; i < n; i++)
	{
		if (str[i] != ' ') // 找到左起第一个非空格位置
		{
			break;
		}
	}
	// 以第一个非空格字符为首字符移动字符串
	for (j = 0; j < n; j++)
	{
		str[j] = str[i];
		i++;
	}
}

#endif