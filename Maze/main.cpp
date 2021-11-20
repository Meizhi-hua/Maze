#include "Maze.h"
#include "Node.h"
#include <iomanip>

using namespace std;

int main()
{
	int sz;		// �Թ���С(��/����)
	cout << "�������Թ���С��" << endl;
	cin >> sz;
	Maze m(sz);	// ���ù��캯�������Թ�
	cout << "��������Թ���" << endl;
	printf("(������%d����С����%d,����Ӧ�ﵽ%d�����)\n", m.getMax(), m.getMin(), m.getLeast());
	m.printMaze();	// ��ӡ�Թ�
	printf("(����=%d������Ҫ��)", m.getEdges().size());
	int start, end;
	cout << "�����������ڵ�ID��" << endl;
	while (true)	// �ж������Ƿ�Ϸ���ѭ�������Ϸ�����������
	{
		cin >> start >> end;
		if (start < 0 || end > sz * sz - 1)
		{
			printf("���벻�Ϸ����ڵ�IDӦ���ڵ���0��С��%d\n", sz * sz);
			printf("���������룺\n");
		}
		else
			break;
	}
	vector<vector<int>> prev_nodes = m.Dijkstra(start, end);			// ǰ��������飬������Dijkstraע��
	vector<vector<int>> paths = m.printPaths(start, end, prev_nodes);	// �������·�����ɵ�����
	printf("�ڵ�%d��%d֮������·������Ϊ%d\n", start, end, paths[0].size() - 1);
	for (auto i : paths)
	{
		for (auto j : i)												// ����ʽ������·��
		{
			if (j != *(i.end() - 1))
				cout << setw(2) << setfill('0') << j << "->";
			else
				cout << setw(2) << setfill('0') << j << endl;
		}
	}
	return 0;
}