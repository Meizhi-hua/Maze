#pragma once
#include <iostream>

using namespace std;

/* 定义结点类，提供迷宫中的结点信息 */
class Node {
	int id, row, col;		/* id:结点序号		row:结点所在行		col:结点所在列 */
	Node* L, * R, * U, * D;	/* L:左相邻结点		R:右相邻结点		U:上相邻结点		D:下相邻结点*/
public:
	Node(int i, int r, int c) :id(i), row(r), col(c), L(nullptr), R(nullptr), U(nullptr), D(nullptr) {};
	int getID();
	int getRow();
	int getCol();
	Node* getLeft();
	Node* getRight();
	Node* getUp();
	Node* getDown();
	void setLeft(Node* l);
	void setRight(Node* r);
	void setUp(Node* u);
	void setDown(Node* d);
};