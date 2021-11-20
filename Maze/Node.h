#pragma once
#include <iostream>

using namespace std;

/* �������࣬�ṩ�Թ��еĽ����Ϣ */
class Node {
	int id, row, col;		/* id:������		row:���������		col:��������� */
	Node* L, * R, * U, * D;	/* L:�����ڽ��		R:�����ڽ��		U:�����ڽ��		D:�����ڽ��*/
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