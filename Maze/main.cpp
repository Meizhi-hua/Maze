#include "Maze.h"
#include "Node.h"
#include <iomanip>

using namespace std;

int main()
{
	int sz;		// 迷宫大小(行/列数)
	cout << "请输入迷宫大小：" << endl;
	cin >> sz;
	Maze m(sz);	// 调用构造函数生成迷宫
	cout << "生成随机迷宫：" << endl;
	printf("(最大边数%d，最小边数%d,边数应达到%d或更多)\n", m.getMax(), m.getMin(), m.getLeast());
	m.printMaze();	// 打印迷宫
	printf("(边数=%d，符合要求)", m.getEdges().size());
	int start, end;
	cout << "请输入两个节点ID：" << endl;
	while (true)	// 判断输入是否合法的循环，不合法则重新输入
	{
		cin >> start >> end;
		if (start < 0 || end > sz * sz - 1)
		{
			printf("输入不合法！节点ID应大于等于0，小于%d\n", sz * sz);
			printf("请重新输入：\n");
		}
		else
			break;
	}
	vector<vector<int>> prev_nodes = m.Dijkstra(start, end);			// 前驱结点数组，见函数Dijkstra注释
	vector<vector<int>> paths = m.printPaths(start, end, prev_nodes);	// 所有最短路径构成的数组
	printf("节点%d和%d之间的最短路径长度为%d\n", start, end, paths[0].size() - 1);
	for (auto i : paths)
	{
		for (auto j : i)												// 按格式输出最短路径
		{
			if (j != *(i.end() - 1))
				cout << setw(2) << setfill('0') << j << "->";
			else
				cout << setw(2) << setfill('0') << j << endl;
		}
	}
	return 0;
}