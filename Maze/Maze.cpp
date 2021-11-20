#include <vector>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <algorithm>

#include "Maze.h"

/*
* 
* Description: Ĭ�Ϲ��캯�������ø�������Ĭ��ֵ
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
* Description: ���캯������������Թ���С�����Թ���
* 
* @param	s: �Թ���С
*/
Maze::Maze(int s)
{
	// ����s���ó�Աֵ
	sz = s;
	least_edges = (3 * sz + 1) * (sz - 1) % 2 == 0 ? (3 * sz + 1) * (sz - 1) / 2 : (3 * sz + 1) * (sz - 1) / 2 + 1;
	max_edges = 2 * sz * (sz - 1);
	min_edges = sz * sz - 1;

	// ����s*s�������ڴ棬����nodes��
	for (int i = 0; i != s*s; ++i)
		nodes.push_back(new Node(i, i / s, i % s));

	// ���ø������ĳ�Աֵ
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

	// ������������ߣ������ڴ����edges��
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
* Description: ��ȡ�Թ��Ĵ�С
* 
* @return	int:�Թ���szֵ
*/
int Maze::getSize()
{
	return sz;
}

/*
*
* Description: ��ȡ�Թ���������
*
* @return	int:�Թ���max_edgesֵ
*/
int Maze::getMax()
{
	return max_edges;
}

/*
*
* Description: ��ȡ�Թ������ٱ���
*
* @return	int:�Թ���min_edgesֵ
*/
int Maze::getMin()
{
	return min_edges;
}

/*
*
* Description: ��ȡ�Թ���Ӧ�ﵽ����
*
* @return	int:�Թ���least_edgesֵ
*/
int Maze::getLeast()
{
	return least_edges;
}

/*
*
* Description: ��ȡ�Թ��ı�
*
* @return	vector<Edge*>:�Թ���edges����
*/
vector<Edge*> Maze::getEdges()
{
	return edges;
}

/*
*
* Description: ��vΪ��ʼ�㣬���Թ�����������ȱ���
*
* @param	adj:	�Թ����ڽӾ���
* @param	v:		��������ʼ��
* @param	visited:�ѱ����������
*/
void Maze::DFS(vector<vector<int>>& adj, int v,vector<int>& visited)
{
	int p;
	visited[v] = 1;					// ���ѷ��ʱ��
	for (int i = 0; i != sz*sz; i++)// ѭ���ҳ�v�ĵ�һ���ڽӽ��
	{
		if (adj[v][i] < 999)
		{
			p = i;
			break;
		}
	}
	for(int i = p; i != sz*sz;i++)	// ��idΪp�Ľ���ѱ����ʣ���ѭ���ҳ�v����һ���ڽӽڵ�
	{
		if (adj[v][i] < 999)
			p = i;
		if (!visited[p])			// ��idΪp�Ľ��δ�����ʣ���ݹ���ʸý��
			DFS(adj, p, visited);
	}
}

/*
* 
* Description: ��nodes�����ͨ��������Թ�
*/
void Maze::connectMaze()
{
	srand((unsigned)time(NULL));							// �����������
	random_shuffle(edges.begin(), edges.end());				// ��edges��������
	vector<Edge*> other_edges(edges.begin() + least_edges, edges.end());
	edges.erase(edges.begin() + least_edges, edges.end());	// ֻ����edges��ǰleast_edges������
															// ������ﵽ��������Թ���Ч��
	setAdj();												// �����ڽӾ���
	vector<int> visited(sz * sz, 0);						// ��ʼ���ѷ�������
	auto p = edges[0]->getElem()[0];						// ȡһ������Ϊ���
	DFS(adj, p->getID(), visited);							// ����������ȱ���
	for (auto i :nodes)										// ���������Ľ�����connected_nodes����
		if (visited[i->getID()])
			connected_nodes.insert(i);
	if (connected_nodes.size() == sz * sz)					// �ж����н�������ͨ
	{
		srand((unsigned)time(NULL));
		if (max_edges != edges.size())						// ���������ӱߣ�������max_edges
		{
			int addition = rand() % (max_edges - edges.size());
			for (int i = 0; i != addition && i != other_edges.size(); i++)
				edges.push_back(other_edges[i]);
		}
	}
	else													// ��δ��ͨ����δ��ͨ�����ͨ
	{
		for (auto n : nodes)
		{
			if (connected_nodes.find(n) == connected_nodes.end())	// ��connected_nodes��δ�ҵ�n
			{
				for (auto i = other_edges.begin(); i != other_edges.end(); i++)
				{
					if ((*i)->exist(n))								// �ҵ�����n�Ĳ���edges�еı�
					{
						for (auto j : (*i)->getElem())				// ȷ�ϸñߵ���һ�˵�����ͨ
						{
							bool flag = false;
							for (auto m : connected_nodes)
								if (j == m)
								{
									edges.push_back(*i);			// ���ñ߼���edges����
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
* Description: ���ñߵ��������
*/
void Maze::setEdges()
{
	for (int i = 0; i != MAX_SIZE; i++)
		for (int j = 0; j != 2 * MAX_SIZE; j++)
			show_edges[i][j] = ' ';				// ��ʼ�������������Ԫ��Ϊ�ո�
	for (auto i : edges)						// ��edges����������Ԫ�ؽ��в���
	{
		Node* n1 = (*i).getElem()[0];			// i��һ���˵�
		Node* n2 = (*i).getElem()[1];			// i����һ�˵�
		if (n2->getCol() - n1->getCol() == 1)	// ��n1��n2����࣬�����øô��������Ϊ'-'
			show_edges[n1->getRow() * 2][n1->getCol()] = '-';
		else									// ��n1��n2���ϲ࣬�����øô��������Ϊ'|'
			show_edges[n1->getRow() * 2 + 1][n1->getCol()] = '|';
	}
}

/*
* 
* Description: �����ڽӾ���
*/
void Maze::setAdj()
{
	for (int i = 0; i != sz * sz; i++)			// ��ʼ���ڽӾ�������Ԫ��Ϊ999
		adj.push_back(vector<int>(sz * sz, 999));
	for (auto i : edges)						// ��edges������Ԫ�����˵��Ӧ�ڽӾ���Ԫ������Ϊ1
	{
		adj[i->getElem()[0]->getID()][i->getElem()[1]->getID()] = 1;
		adj[i->getElem()[1]->getID()][i->getElem()[0]->getID()] = 1;
	}
}

/*
* 
* Description: ��ӡ�Թ�
*/
void Maze::printMaze()
{
	connectMaze();	// �����ͨ�Թ�
	setEdges();		// ���ñߵ��������
	for (int row = 0; row != sz; row++)
	{
		for (int i = row * sz, j = 0; i != (row + 1) * sz; i++, j++) // ���Ԫ�ؼ����ѭ��
		{
			if (j != sz - 1)	// δ�����һ��Ԫ��ʱ��˳�����Ԫ�ؼ����
			{
				cout << setw(2) << setfill('0') << nodes[i]->getID();
				cout << show_edges[row * 2][j];
			}
			else				// �����һ��ʱ�����ĩλԪ��
				cout << setw(2) << setfill('0') << nodes[i]->getID() << endl;
		}	
		if (row != sz - 1)		// δ�����һ��Ԫ��ʱ������ݱ�������
		{
			cout << setw(2) << setfill(' ') << show_edges[2 * row + 1][0];		// ��һ����ռ������λ
			for (int i = 1; i != sz; i++)
				cout << setw(3) << setfill(' ') << show_edges[2 * row + 1][i];	// �����ռ������λ
			cout << endl;
		}
	}
}

/*
* 
* Description: ��ȡ�Թ���ʼ���
* 
* @return	Node*:�����Թ���һ�����
*/
Node* Maze::getBegin()
{
	return nodes[0];
}

/*
* 
* Description:	ʹ��Dijkstra�㷨������Ϊstart��end�����·��
*				����Dijkstra�㷨ֻ��������һ�����·����Ϊ�˱����������·��
*				����prev_nodes����洢start����������·����ǰ�����
*				֮���ٲ���DFS˼�뽫��·�����
* 
* @param	start:					��ʼ�����
* @param	end:					�յ�����
* @return	vector<vector<int>>:	���ظ�����ǰ�����
*/
vector<vector<int>> Maze::Dijkstra(int start, int end)
{
	setAdj();											// �����ڽӾ���
	vector<vector<int>> prev_nodes(sz * sz, { start });	// ��ʼ��ǰ��������飬��Ԫ�س�ʼֵΪstart
														// prev_nodes[i]��ʾ��i������ǰ�����
	vector<int> dis = adj[start];						// �洢start����������·���ĳ���
	set<int> visited{ start };							// �洢�ѷ��ʽ���ŵļ��ϣ���ʼ��Ϊ{start}
	while (visited.size() != sz * sz)					// ѭ��ֱ�����н�㶼������
	{
		int close = 999;								// ��ʼ�����·��·������Ϊ999
		int close_point;								// �洢��ǰ���·�����յ�
		for (int i = 0; i != sz * sz; i++)
		{
			if (dis[i] < close && visited.find(i) == visited.end()) // iδ��������start��i�ľ���С����̾���ʱ��
																	// ����ǰ���·�����յ�����Ϊi����������Ϊdis[i]
			{
				close_point = i;
				close == dis[i];
				break;
			}
		}
		for (int j = 0; j != sz * sz; j++)
		{
			if (adj[close_point][j] < 999 && j != start)			// ȷ��j��close_point��ͨ��j��Ϊ���
			{
				if (dis[close_point] + adj[close_point][j] < dis[j])// ��ͨ��close_point����j�����dis���Ѵ洢��j�ľ���С
																	// ���û�dis[j]��ֵ��������ǰ����㼯Ϊ����close_point
				{
					dis[j] = dis[close_point] + adj[close_point][j];
					prev_nodes[j].clear();
					prev_nodes[j].push_back(close_point);
				}
				else if (dis[close_point] + adj[close_point][j] == dis[j])	// ��ͨ��close_point����j�������dis���Ѵ洢��j�ľ���
																			// ������ǰ�����ֵ�м���j
					prev_nodes[j].push_back(close_point);
			}
		}
		visited.insert(close_point);										// ��close_point��Ϊ�ѷ���
	}
	return prev_nodes;
}

/*
* 
* Description: ��DFS˼��ݹ�ش�ӡ��ǰ����㼯��Ӧ��·��
* 
* @param	start:		·�����
* @param	end:		·���յ�
* @param	prev_nodes:	ǰ����㼯
* @return	vector<vector<int>>: ����start��end���������·��
*/
vector<vector<int>> Maze::printPaths(int start, int end, vector<vector<int>>& prev_nodes) {
	vector<vector<int>> childPaths;	// �ݹ�����в��������·������·��
	vector<vector<int>> midPaths;	// �����������·��������
	if (end != start) {
		for (int i = 0; i < prev_nodes[end].size(); ++i) {
			childPaths = printPaths(start, prev_nodes[end][i], prev_nodes); // �ݹ�ص����
			for (int j = 0; j < childPaths.size(); ++j) {
				childPaths[j].push_back(end);								// ���뵱ǰ���֮��Ľ��
			}
			if (midPaths.empty()) {
				midPaths = childPaths;										// ��Ϊ�գ���childPaths��ֵ��midPaths
			}
			else {
				midPaths.insert(midPaths.end(), childPaths.begin(), childPaths.end()); // ���ǿգ���midPathsĩβ����childPaths
			}
		}
	}
	else {	// �ݹ�ÿ�ص����ʱ��������㣬��������¼�µ�һ�����·��
		midPaths.push_back(vector<int>(1, start));
	}
	return midPaths;
}

/*
* 
* Description: ������������������ڴ�黹ϵͳ
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