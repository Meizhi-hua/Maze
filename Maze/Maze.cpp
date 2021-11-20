#include <vector>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <algorithm>

#include "Maze.h"

/*
* 
* Description: 默认构造函数，设置各参数的默认值
*/
Maze::Maze()
{
	sz = 0;
	connected_nodes.insert(nodes[0]);
	least_edges = 0;
	max_edges = 0;
}

/*
* 
* Description: 构造函数，按输入的迷宫大小构造迷宫类
* 
* @param	s: 迷宫大小
*/
Maze::Maze(int s)
{
	// 按照s设置成员值
	sz = s;
	least_edges = (3 * sz + 1) * (sz - 1) % 2 == 0 ? (3 * sz + 1) * (sz - 1) / 2 : (3 * sz + 1) * (sz - 1) / 2 + 1;
	max_edges = 2 * sz * (sz - 1);
	min_edges = sz * sz - 1;

	// 申请s*s个结点的内存，存入nodes中
	for (int i = 0; i != s*s; ++i)
		nodes.push_back(new Node(i, i / s, i % s));

	// 设置各个结点的成员值
	for (int i = 0; i != s*s; ++i)
	{
		if (nodes[i]->getCol() != 0)
			nodes[i]->setLeft(nodes[i - 1]);
		if (nodes[i]->getCol() != sz - 1)
			nodes[i]->setRight(nodes[i + 1]);
		if (nodes[i]->getRow() != 0)
			nodes[i]->setUp(nodes[i - sz]);
		if (nodes[i]->getRow() != sz - 1)
			nodes[i]->setDown(nodes[i + sz]);
	}

	// 将结点两两连边，申请内存存入edges中
	for (int i = 0; i != s * s; ++i)
	{
		if (nodes[i]->getCol() != sz - 1)
			edges.push_back(new Edge(nodes[i], nodes[i + 1]));
		if (nodes[i]->getRow() != sz - 1)
			edges.push_back(new Edge(nodes[i], nodes[i + sz]));
	}
}

/*
* 
* Description: 获取迷宫的大小
* 
* @return	int:迷宫的sz值
*/
int Maze::getSize()
{
	return sz;
}

/*
*
* Description: 获取迷宫的最大边数
*
* @return	int:迷宫的max_edges值
*/
int Maze::getMax()
{
	return max_edges;
}

/*
*
* Description: 获取迷宫的最少边数
*
* @return	int:迷宫的min_edges值
*/
int Maze::getMin()
{
	return min_edges;
}

/*
*
* Description: 获取迷宫的应达到边数
*
* @return	int:迷宫的least_edges值
*/
int Maze::getLeast()
{
	return least_edges;
}

/*
*
* Description: 获取迷宫的边
*
* @return	vector<Edge*>:迷宫的edges数组
*/
vector<Edge*> Maze::getEdges()
{
	return edges;
}

/*
*
* Description: 以v为起始点，对迷宫进行深度优先遍历
*
* @param	adj:	迷宫的邻接矩阵
* @param	v:		遍历的起始点
* @param	visited:已遍历结点数组
*/
void Maze::DFS(vector<vector<int>>& adj, int v,vector<int>& visited)
{
	int p;
	visited[v] = 1;					// 置已访问标记
	for (int i = 0; i != sz*sz; i++)// 循环找出v的第一个邻接结点
	{
		if (adj[v][i] < 999)
		{
			p = i;
			break;
		}
	}
	for(int i = p; i != sz*sz;i++)	// 若id为p的结点已被访问，则循环找出v的下一个邻接节点
	{
		if (adj[v][i] < 999)
			p = i;
		if (!visited[p])			// 若id为p的结点未被访问，则递归访问该结点
			DFS(adj, p, visited);
	}
}

/*
* 
* Description: 将nodes随机连通生成随机迷宫
*/
void Maze::connectMaze()
{
	srand((unsigned)time(NULL));							// 设置随机种子
	random_shuffle(edges.begin(), edges.end());				// 将edges数组乱序
	vector<Edge*> other_edges(edges.begin() + least_edges, edges.end());
	edges.erase(edges.begin() + least_edges, edges.end());	// 只保留edges的前least_edges个对象，
															// 由乱序达到随机生成迷宫的效果
	setAdj();												// 设置邻接矩阵
	vector<int> visited(sz * sz, 0);						// 初始化已访问数组
	auto p = edges[0]->getElem()[0];						// 取一随机结点为起点
	DFS(adj, p->getID(), visited);							// 进行深度优先遍历
	for (auto i :nodes)										// 将遍历到的结点存入connected_nodes数组
		if (visited[i->getID()])
			connected_nodes.insert(i);
	if (connected_nodes.size() == sz * sz)					// 判断所有结点均已连通
	{
		srand((unsigned)time(NULL));
		if (max_edges != edges.size())						// 随机继续添加边，不超过max_edges
		{
			int addition = rand() % (max_edges - edges.size());
			for (int i = 0; i != addition && i != other_edges.size(); i++)
				edges.push_back(other_edges[i]);
		}
	}
	else													// 若未连通，则将未连通结点连通
	{
		for (auto n : nodes)
		{
			if (connected_nodes.find(n) == connected_nodes.end())	// 若connected_nodes中未找到n
			{
				for (auto i = other_edges.begin(); i != other_edges.end(); i++)
				{
					if ((*i)->exist(n))								// 找到包含n的不在edges中的边
					{
						for (auto j : (*i)->getElem())				// 确认该边的另一端点已连通
						{
							bool flag = false;
							for (auto m : connected_nodes)
								if (j == m)
								{
									edges.push_back(*i);			// 将该边加入edges数组
									flag = true;
									break;
								}
							if (flag)
								break;
						}
					}
				}
			}
		}
	}
}

/*
* 
* Description: 设置边的输出阵列
*/
void Maze::setEdges()
{
	for (int i = 0; i != MAX_SIZE; i++)
		for (int j = 0; j != 2 * MAX_SIZE; j++)
			show_edges[i][j] = ' ';				// 初始化输出阵列所有元素为空格
	for (auto i : edges)						// 对edges数组中所有元素进行操作
	{
		Node* n1 = (*i).getElem()[0];			// i的一个端点
		Node* n2 = (*i).getElem()[1];			// i的另一端点
		if (n2->getCol() - n1->getCol() == 1)	// 若n1在n2的左侧，则设置该处输出阵列为'-'
			show_edges[n1->getRow() * 2][n1->getCol()] = '-';
		else									// 若n1在n2的上侧，则设置该处输出阵列为'|'
			show_edges[n1->getRow() * 2 + 1][n1->getCol()] = '|';
	}
}

/*
* 
* Description: 设置邻接矩阵
*/
void Maze::setAdj()
{
	for (int i = 0; i != sz * sz; i++)			// 初始化邻接矩阵所有元素为999
		adj.push_back(vector<int>(sz * sz, 999));
	for (auto i : edges)						// 将edges中所有元素两端点对应邻接矩阵元素设置为1
	{
		adj[i->getElem()[0]->getID()][i->getElem()[1]->getID()] = 1;
		adj[i->getElem()[1]->getID()][i->getElem()[0]->getID()] = 1;
	}
}

/*
* 
* Description: 打印迷宫
*/
void Maze::printMaze()
{
	connectMaze();	// 随机连通迷宫
	setEdges();		// 设置边的输出阵列
	for (int row = 0; row != sz; row++)
	{
		for (int i = row * sz, j = 0; i != (row + 1) * sz; i++, j++) // 输出元素及横边循环
		{
			if (j != sz - 1)	// 未到最后一个元素时，顺序输出元素及横边
			{
				cout << setw(2) << setfill('0') << nodes[i]->getID();
				cout << show_edges[row * 2][j];
			}
			else				// 到最后一行时，输出末位元素
				cout << setw(2) << setfill('0') << nodes[i]->getID() << endl;
		}	
		if (row != sz - 1)		// 未到最后一行元素时，输出纵边所在行
		{
			cout << setw(2) << setfill(' ') << show_edges[2 * row + 1][0];		// 第一条边占两个单位
			for (int i = 1; i != sz; i++)
				cout << setw(3) << setfill(' ') << show_edges[2 * row + 1][i];	// 其余边占三个单位
			cout << endl;
		}
	}
}

/*
* 
* Description: 获取迷宫起始结点
* 
* @return	Node*:返回迷宫第一个结点
*/
Node* Maze::getBegin()
{
	return nodes[0];
}

/*
* 
* Description:	使用Dijkstra算法求结点编号为start到end的最短路径
*				由于Dijkstra算法只适用于求一条最短路径，为了保存所有最短路径
*				设置prev_nodes数组存储start到各结点最短路径的前驱结点
*				之后再采用DFS思想将各路径输出
* 
* @param	start:					起始结点编号
* @param	end:					终点结点编号
* @return	vector<vector<int>>:	返回各结点的前驱结点
*/
vector<vector<int>> Maze::Dijkstra(int start, int end)
{
	setAdj();											// 设置邻接矩阵
	vector<vector<int>> prev_nodes(sz * sz, { start });	// 初始化前驱结点数组，各元素初始值为start
														// prev_nodes[i]表示第i个结点的前驱结点
	vector<int> dis = adj[start];						// 存储start到各结点最短路径的长度
	set<int> visited{ start };							// 存储已访问结点编号的集合，初始化为{start}
	while (visited.size() != sz * sz)					// 循环直到所有结点都被遍历
	{
		int close = 999;								// 初始化最短路径路径长度为999
		int close_point;								// 存储当前最短路径的终点
		for (int i = 0; i != sz * sz; i++)
		{
			if (dis[i] < close && visited.find(i) == visited.end()) // i未被遍历且start到i的距离小于最短距离时，
																	// 将当前最短路径的终点设置为i，距离设置为dis[i]
			{
				close_point = i;
				close == dis[i];
				break;
			}
		}
		for (int j = 0; j != sz * sz; j++)
		{
			if (adj[close_point][j] < 999 && j != start)			// 确认j与close_point连通且j不为起点
			{
				if (dis[close_point] + adj[close_point][j] < dis[j])// 若通过close_point到达j距离比dis中已存储到j的距离小
																	// 则置换dis[j]的值，且重置前驱结点集为仅有close_point
				{
					dis[j] = dis[close_point] + adj[close_point][j];
					prev_nodes[j].clear();
					prev_nodes[j].push_back(close_point);
				}
				else if (dis[close_point] + adj[close_point][j] == dis[j])	// 若通过close_point到达j距离等于dis中已存储到j的距离
																			// 则在其前驱结点值中加入j
					prev_nodes[j].push_back(close_point);
			}
		}
		visited.insert(close_point);										// 将close_point置为已访问
	}
	return prev_nodes;
}

/*
* 
* Description: 用DFS思想递归地打印出前驱结点集对应的路径
* 
* @param	start:		路径起点
* @param	end:		路径终点
* @param	prev_nodes:	前驱结点集
* @return	vector<vector<int>>: 返回start到end的所有最短路径
*/
vector<vector<int>> Maze::printPaths(int start, int end, vector<vector<int>>& prev_nodes) {
	vector<vector<int>> childPaths;	// 递归过程中产生的最短路径的子路径
	vector<vector<int>> midPaths;	// 存入所有最短路径的数组
	if (end != start) {
		for (int i = 0; i < prev_nodes[end].size(); ++i) {
			childPaths = printPaths(start, prev_nodes[end][i], prev_nodes); // 递归回到起点
			for (int j = 0; j < childPaths.size(); ++j) {
				childPaths[j].push_back(end);								// 存入当前结点之后的结点
			}
			if (midPaths.empty()) {
				midPaths = childPaths;										// 若为空，将childPaths赋值给midPaths
			}
			else {
				midPaths.insert(midPaths.end(), childPaths.begin(), childPaths.end()); // 若非空，在midPaths末尾加入childPaths
			}
		}
	}
	else {	// 递归每回到起点时，存入起点，即开启记录新的一条最短路径
		midPaths.push_back(vector<int>(1, start));
	}
	return midPaths;
}

/*
* 
* Description: 析构函数，将申请的内存归还系统
*/
Maze::~Maze()
{
	for (auto& n : nodes)
	{
		delete n;
		n = nullptr;
	}
	for (auto& e : edges)
	{
		delete e;
		e = nullptr;
	}
}