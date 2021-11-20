#include "Edge.h"

/*
* 
* Description: 以两个节点构造一个Edge类
* 
* @param	n1:边的一端结点
* @param	n2:边的另一端结点
*/
Edge::Edge(Node* n1, Node* n2)
{
	nodes.push_back(n1);
	nodes.push_back(n2);
}

/*
* 
* Description: 判断结点n是否为该edge对象的端点
* 
* @param	n:输入结点
* @return	bool:是端点返回true，否则返回false
*/
bool Edge::exist(Node* n)
{
	for (auto i : nodes)
		if (i == n)
			return true;
	return false;
}

/*
* 
* Description: 获取该Edge对象的端点信息
* 
* @return	vector<Node*>:返回端点数组
*/
vector<Node*> Edge::getElem()
{
	return nodes;
}