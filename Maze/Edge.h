#pragma once
#include <vector>

#include "Node.h"

/* 定义边类，存储迷宫中的边信息 */
class Edge {
	vector<Node*> nodes;	/* 边中结点组，一般为2个 */
public:
	Edge(Node* n1, Node* n2);
	bool exist(Node* n);
	vector<Node*> getElem();
};
