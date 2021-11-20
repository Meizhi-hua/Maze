#include <iostream>

#include "Node.h"

using namespace std;

/*
* 
* Description: ��ȡ��Node����ı��
* 
* @return	int:��Node�����id��Ա
*/
int Node::getID()
{
	return id;
}

/*
*
* Description: ��ȡ��Node������������
*
* @return	int:��Node�����row��Ա
*/
int Node::getRow()
{
	return row;
}

/*
*
* Description: ��ȡ��Node������������
*
* @return	int:��Node�����col��Ա
*/
int Node::getCol()
{
	return col;
}

/*
*
* Description: ��ȡ��Node���������ڽ��
*
* @return	int:��Node�����L��Ա
*/
Node* Node::getLeft()
{
	return L;
}

/*
*
* Description: ��ȡ��Node���������ڽ��
*
* @return	int:��Node�����R��Ա
*/
Node* Node::getRight()
{
	return R;
}

/*
*
* Description: ��ȡ��Node���������ڽ��
*
* @return	int:��Node�����U��Ա
*/
Node* Node::getUp()
{
	return U;
}

/*
*
* Description: ��ȡ��Node���������ڽ��
*
* @return	int:��Node�����D��Ա
*/
Node* Node::getDown()
{
	return D;
}

/*
*
* Description: ������������Ϊ��Node���������ڽ��
*
* @param	u:������
*/
void Node::setUp(Node* u)
{
	U = u;
}

/*
*
* Description: ������������Ϊ��Node���������ڽ��
*
* @param	d:������
*/
void Node::setDown(Node* d)
{
	D = d;
}

/*
*
* Description: ������������Ϊ��Node���������ڽ��
*
* @param	l:������
*/
void Node::setLeft(Node* l)
{
	L = l;
}

/*
*
* Description: ������������Ϊ��Node���������ڽ��
*
* @param	r:������
*/
void Node::setRight(Node* r)
{
	R = r;
}