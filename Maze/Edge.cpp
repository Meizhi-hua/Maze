#include "Edge.h"

/*
* 
* Description: �������ڵ㹹��һ��Edge��
* 
* @param	n1:�ߵ�һ�˽��
* @param	n2:�ߵ���һ�˽��
*/
Edge::Edge(Node* n1, Node* n2)
{
	nodes.push_back(n1);
	nodes.push_back(n2);
}

/*
* 
* Description: �жϽ��n�Ƿ�Ϊ��edge����Ķ˵�
* 
* @param	n:������
* @return	bool:�Ƕ˵㷵��true�����򷵻�false
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
* Description: ��ȡ��Edge����Ķ˵���Ϣ
* 
* @return	vector<Node*>:���ض˵�����
*/
vector<Node*> Edge::getElem()
{
	return nodes;
}