#ifndef CREATE_TREE_H
#define CREATE_TREE_H

#include "Btree.h"
#include <iostream>
#include <cstdio>
#include <cstring>

// ==========================================
// 函数声明部分
// ==========================================

// 初始化树
void initial_tree(struct p_tree &t);

// 获取祖先结点
bool get_ancestor(struct p_tree &t, char x);

// 获取子结点
void get_children(struct p_tree &t, char x);

// 获取第一个孩子下标
int first_child(struct p_tree &t, int v);

// 获取下一个兄弟下标
int next_sibling(struct p_tree &t, int v, int w);

// 先序遍历 (递归)
void pre_order(struct p_tree &t, int v);

// 先序遍历入口
void pre_traverse(struct p_tree &t);

// 后序遍历 (递归)
void post_order(struct p_tree &t, int v);

// 后序遍历入口
void post_traverse(struct p_tree &t);

// 打印树结构
void print_tree(struct p_tree &t);

// 删除左空格
void str_l_trim(char *str);

// 从文件创建树 (双亲表示)
int create_tree_from_file(char file_name[], struct p_tree &t);

// 搜索下一个兄弟
int next_node(struct p_tree t, int w);

// 递归创建孩子兄弟链表树
void create_cs_tree_recursive(struct cs_node *&t, struct p_tree &t1, int v);

// 从双亲表示树创建孩子兄弟链表树
void create_cs_tree(struct cs_node *&t, struct p_tree t1);

// ==========================================
// 定义部分
// ==========================================

#define MAX_LEN 100

// 树的结点结构 (双亲表示)
struct pt_node
{
	char data;
	int parent;
};

// 双亲表示的树结构
struct p_tree
{
	pt_node node[MAX_LEN];
	int n;
};

// 树的孩子兄弟链表表示
struct cs_node
{
	char data;
	cs_node *first_child;
	cs_node *next_sibling;
};

void initial_tree(p_tree &t)
{
	t.n = 0;
}

bool get_ancestor(p_tree &t, char x)
{
	int w = 0;
	char y = x;

	for (w = 0; w < t.n; w++)
	{
		if (t.node[w].data == y)
		{
			w = t.node[w].parent;
			y = t.node[w].data;
			std::cout << y << "\t";
			break;
		}
	}
	if (w >= t.n)
	{
		return false;
	}

	while (w != -1)
	{
		if (t.node[w].data == y)
		{
			w = t.node[w].parent;
			y = t.node[w].data;
			std::cout << y << "\t";
		}
		else
		{
			w = (w + 1) % t.n;
		}
	}
	return true;
}

void get_children(p_tree &t, char x)
{
	int i, w;
	for (w = 0; w < t.n; w++)
	{
		if (t.node[w].data == x)
		{
			break;
		}
	}
	if (w >= t.n)
	{
		return;
	}
	for (i = 0; i < t.n; i++)
	{
		if (t.node[i].parent == w)
		{
			std::cout << t.node[i].data << "\t";
		}
	}
	std::cout << std::endl;
}

int first_child(p_tree &t, int v)
{
	int w;
	if (v == -1)
	{
		return -1;
	}

	for (w = 0; w < t.n; w++)
	{
		if (t.node[w].parent == v)
		{
			return w;
		}
	}
	return -1;
}

int next_sibling(p_tree &t, int v, int w)
{
	int i;
	for (i = w + 1; i < t.n; i++)
	{
		if (t.node[i].parent == v)
		{
			return i;
		}
	}
	return -1;
}

void pre_order(p_tree &t, int v)
{
	int w;
	std::cout << t.node[v].data << "\t";

	w = first_child(t, v);
	while (w != -1)
	{
		pre_order(t, w);
		w = next_sibling(t, v, w);
	}
}

void pre_traverse(p_tree &t)
{
	int i;
	for (i = 0; i < t.n; i++)
	{
		if (t.node[i].parent == -1)
		{
			pre_order(t, i);
		}
	}
}

void post_order(p_tree &t, int v)
{
	int w;
	w = first_child(t, v);
	while (w != -1)
	{
		post_order(t, w);
		w = next_sibling(t, v, w);
	}
	std::cout << t.node[v].data << "\t";
}

void post_traverse(p_tree &t)
{
	int i;
	for (i = 0; i < t.n; i++)
	{
		if (t.node[i].parent == -1)
		{
			post_order(t, i);
		}
	}
}

void print_tree(p_tree &t)
{
	int i;
	std::cout << "下标\t结点\t双亲" << std::endl;
	for (i = 0; i < t.n; i++)
	{
		std::cout << i << "\t" << t.node[i].data << "\t" << t.node[i].parent << std::endl;
	}
}

void str_l_trim(char *str)
{
	int i, j;
	int n = 0;
	n = (int)std::strlen(str) + 1;
	for (i = 0; i < n; i++)
	{
		if (str[i] != ' ')
		{
			break;
		}
	}
	for (j = 0; j < n; j++)
	{
		str[j] = str[i];
		i++;
	}
}

int create_tree_from_file(char file_name[], p_tree &t)
{
	std::FILE *p_file;
	char str[1000];
	char str_temp[10];

	int i = 0, j = 0;

	p_file = std::fopen(file_name, "r");
	if (!p_file)
	{
		std::printf("错误：文件%s打开失败。\n", file_name);
		return false;
	}

	while (std::fgets(str, 1000, p_file) != NULL)
	{
		str_l_trim(str);
		if (str[0] == '\n')
		{
			continue;
		}

		std::strncpy(str_temp, str, 2);
		if (std::strstr(str_temp, "//") != NULL)
		{
			continue;
		}
		else
		{
			break;
		}
	}

	if (std::strstr(str, "Tree or Forest") == NULL)
	{
		std::printf("错误：打开的文件格式错误！\n");
		std::fclose(p_file);
		return false;
	}

	while (std::fgets(str, 1000, p_file) != NULL)
	{
		str_l_trim(str);
		if (str[0] == '\n')
		{
			continue;
		}

		std::strncpy(str_temp, str, 2);
		if (std::strstr(str_temp, "//") != NULL)
		{
			continue;
		}
		else
		{
			break;
		}
	}

	char *token = std::strtok(str, " ");
	int n_num = 0;
	while (token != NULL)
	{
		t.node[n_num].data = *token;
		t.node[n_num].parent = -1;
		token = std::strtok(NULL, " ");
		n_num++;
	}

	int n_p;
	int n_c;
	char n_f, n_s;

	while (std::fgets(str, 1000, p_file) != NULL)
	{
		str_l_trim(str);
		if (str[0] == '\n')
		{
			continue;
		}

		std::strncpy(str_temp, str, 2);
		if (std::strstr(str_temp, "//") != NULL)
		{
			continue;
		}

		char *token = std::strtok(str, " ");

		if (token == NULL)
		{
			std::printf("错误：读取树的边数据失败！\n");
			std::fclose(p_file);
			return false;
		}
		n_f = *token;

		token = std::strtok(NULL, " ");
		if (token == NULL)
		{
			std::printf("错误：读取树的边数据失败！\n");
			std::fclose(p_file);
			return false;
		}
		n_s = *token;

		for (n_p = 0; n_p < n_num; n_p++)
		{
			if (t.node[n_p].data == n_f)
			{
				break;
			}
		}
		for (n_c = 0; n_c < n_num; n_c++)
		{
			if (t.node[n_c].data == n_s)
			{
				break;
			}
		}

		t.node[n_c].parent = n_p;
	}

	t.n = n_num;
	std::fclose(p_file);
	return true;
}

int next_node(p_tree t, int w)
{
	int i;
	for (i = w + 1; i < t.n; i++)
	{
		if (t.node[w].parent == t.node[i].parent)
		{
			return i;
		}
	}
	return -1;
}

void create_cs_tree_recursive(cs_node *&t, p_tree &t1, int v)
{
	int w;
	t = new cs_node;
	t->data = t1.node[v].data;
	t->first_child = NULL;
	t->next_sibling = NULL;
	w = first_child(t1, v);
	if (w != -1)
	{
		create_cs_tree_recursive(t->first_child, t1, w);
	}

	w = next_node(t1, v);
	if (w != -1)
	{
		create_cs_tree_recursive(t->next_sibling, t1, w);
	}
}

void create_cs_tree(cs_node *&t, p_tree t1)
{
	int i;
	for (i = 0; i < t1.n; i++)
	{
		if (t1.node[i].parent == -1)
		{
			break;
		}
	}
	if (i < t1.n)
	{
		create_cs_tree_recursive(t, t1, i);
	}
}

#endif