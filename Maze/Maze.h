#pragma once
#include <iostream>
#include <vector>
#include <set>

#include "Node.h"
#include "Edge.h"

using namespace std;

#define MAX_SIZE 15

/* 定义迷宫类 */
class Maze {
	int sz;												/* 迷宫大小(行/列数) */
	int min_edges, max_edges, least_edges;				/* min_edges:最少边数	max_edges:最大边数	
														least_edges:应达到边数，一般为最少与最大的平均值 */
	vector<Node*> nodes;								/* 迷宫中结点组 */
	vector<Edge*> edges;								/* 迷宫中边组	*/
	set<Node*> connected_nodes;							/* 记录已连通结点的数组，以便将所有结点连通 */
	vector<vector<int>> adj;							/* 邻接矩阵		*/
	char show_edges[2 * MAX_SIZE - 1][MAX_SIZE - 1];	/* 边的输出阵列 */
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