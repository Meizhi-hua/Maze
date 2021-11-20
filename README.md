# Maze
to find all the shortest paths in a randomly generated maze using Dijkstra and DFS
> 连接矩阵的点随机生成迷宫，使用迪克斯特拉算法和DFS（深度优先遍历）找到所有的最短路径

## Development environment
- Operating system: Windows 11
- IDE: Microsoft Visual Studio 2019

## Description
It's a work that needed to use Dijkstra algorithm to find **all the shortest paths** in a randomly generated maze.The maze must be all-connected.
Details are listed below:
- Input the size of the maze N to generate a N*N matrix.
- Add the edges between nodes to make all nodes connected.
- Output the maze with '|' for vertical sides and '-' for horizonal sides.
- Continue adding sides to make the number of sides no less than the average of the minimum N^2-1 and the max 2N(N-1).
- Use Dijkstra to find all the shortest paths between two nodes that user input and output the length and paths.
- Description in Chinese is before:
- ![image](https://github.com/Meizhi-hua/Maze/blob/main/pngs/CSample.png)

## Samples
![image](https://github.com/Meizhi-hua/Maze/blob/main/pngs/sample.png)
