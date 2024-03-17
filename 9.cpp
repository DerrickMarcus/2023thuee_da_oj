#include <cstdio>
#include <vector>
// #include <cstdlib>
// #include <algorithm>
// #include <cmath>

struct Node
{
    int Start;
    int Time;
    int Cost;
};

int searchPath(int current, int START, int cur_time, int cur_cost, int TIME, std::vector<std::vector<Node>> &graph, std::vector<bool> &visited)
{
    // 在当前节点处，在时间限制下，能够到达终点的最低价格。如果不能到达终点或者时间超出限制，返回无穷大
    if (current == START && cur_time <= TIME)
    {
        return cur_cost;
    }
    if (graph[current].empty())
    {
        return 0x7fffffff;
    }
    int flag = 0;
    int min_cost = 0x7fffffff;
    for (const Node &neighbor : graph[current])
    {
        if (visited[neighbor.Start] == false)
        {
            if (cur_time + neighbor.Time > TIME)
            {
                continue; // 已经超时，提前退出
            }
            else
            {
                visited[neighbor.Start] = true;
                int cost = searchPath(neighbor.Start, START, cur_time + neighbor.Time, cur_cost + neighbor.Cost, TIME, graph, visited);
                if (cost < min_cost)
                {
                    min_cost = cost;
                }
                visited[neighbor.Start] = false;
                flag = 1;
            }
        }
    }
    if (flag == 0)
    {
        return 0x7fffffff; // 没有可以访问的节点
    }
    return min_cost;
}

int main()
{
    int N, M; // N个节点，M条边
    scanf("%d%d", &N, &M);
    int START, END, TIME; // 小明的起点和终点，时间限制
    std::vector<std::vector<Node>> graph(N);
    for (int i = 0; i < M; i++)
    {
        int start, end, time, cost;
        scanf("%d%d%d%d", &start, &end, &time, &cost);
        graph[end].push_back({start, time, cost});
    }
    scanf("%d%d%d", &START, &END, &TIME);

    int cur_time = 0, cur_cost = 0;
    std::vector<bool> visited(N, false);
    int min_cost = searchPath(END, START, cur_time, cur_cost, TIME, graph, visited);

    if (min_cost == 0x7fffffff)
    {
        printf("%d", -1);
    }
    else
    {
        printf("%d", min_cost);
    }
    return 0;
}
