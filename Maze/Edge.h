#pragma once
#include <vector>

#include "Node.h"

/* ������࣬�洢�Թ��еı���Ϣ */
class Edge {
	vector<Node*> nodes;	/* ���н���飬һ��Ϊ2�� */
public:
	Edge(Node* n1, Node* n2);
	bool exist(Node* n);
	vector<Node*> getElem();
};
