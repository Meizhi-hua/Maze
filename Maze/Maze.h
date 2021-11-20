#pragma once
#include <iostream>
#include <vector>
#include <set>

#include "Node.h"
#include "Edge.h"

using namespace std;

#define MAX_SIZE 15

/* �����Թ��� */
class Maze {
	int sz;												/* �Թ���С(��/����) */
	int min_edges, max_edges, least_edges;				/* min_edges:���ٱ���	max_edges:������	
														least_edges:Ӧ�ﵽ������һ��Ϊ����������ƽ��ֵ */
	vector<Node*> nodes;								/* �Թ��н���� */
	vector<Edge*> edges;								/* �Թ��б���	*/
	set<Node*> connected_nodes;							/* ��¼����ͨ�������飬�Ա㽫���н����ͨ */
	vector<vector<int>> adj;							/* �ڽӾ���		*/
	char show_edges[2 * MAX_SIZE - 1][MAX_SIZE - 1];	/* �ߵ�������� */
public:
	Maze();
	Maze(int s);
	void setEdges();
	void setAdj();
	int getSize();
	Node* getBegin();
	vector<Edge*> getEdges();
	int getMax();
	int getMin();
	int getLeast();
	void printMaze();
	void connectMaze();
	void DFS(vector<vector<int>>& adj, int v, vector<int>& visited);
	vector<vector<int>> Dijkstra(int start, int end);
	vector<vector<int>> printPaths(int start, int end, vector<vector<int>>& prev_nodes);
	~Maze();
};