#include <iostream>

#include "Node.h"

using namespace std;

/*
* 
* Description: 获取该Node对象的编号
* 
* @return	int:该Node对象的id成员
*/
int Node::getID()
{
	return id;
}

/*
*
* Description: 获取该Node对象所在行数
*
* @return	int:该Node对象的row成员
*/
int Node::getRow()
{
	return row;
}

/*
*
* Description: 获取该Node对象所在列数
*
* @return	int:该Node对象的col成员
*/
int Node::getCol()
{
	return col;
}

/*
*
* Description: 获取该Node对象左相邻结点
*
* @return	int:该Node对象的L成员
*/
Node* Node::getLeft()
{
	return L;
}

/*
*
* Description: 获取该Node对象右相邻结点
*
* @return	int:该Node对象的R成员
*/
Node* Node::getRight()
{
	return R;
}

/*
*
* Description: 获取该Node对象上相邻结点
*
* @return	int:该Node对象的U成员
*/
Node* Node::getUp()
{
	return U;
}

/*
*
* Description: 获取该Node对象下相邻结点
*
* @return	int:该Node对象的D成员
*/
Node* Node::getDown()
{
	return D;
}

/*
*
* Description: 将输入结点设置为该Node对象上相邻结点
*
* @param	u:输入结点
*/
void Node::setUp(Node* u)
{
	U = u;
}

/*
*
* Description: 将输入结点设置为该Node对象下相邻结点
*
* @param	d:输入结点
*/
void Node::setDown(Node* d)
{
	D = d;
}

/*
*
* Description: 将输入结点设置为该Node对象左相邻结点
*
* @param	l:输入结点
*/
void Node::setLeft(Node* l)
{
	L = l;
}

/*
*
* Description: 将输入结点设置为该Node对象右相邻结点
*
* @param	r:输入结点
*/
void Node::setRight(Node* r)
{
	R = r;
}