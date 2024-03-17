#include <cstdio>
#include <vector>

int DFS_1(std::vector<std::vector<int>> &graph, int N)
{
    std::vector<int> stk;
    std::vector<bool> visited(N, false);

    stk.push_back(0); // 栈实现深度优先遍历
    visited[0] = true;
    int sum = 1;

    while (stk.size() != 0)
    {
        int temp = stk[stk.size() - 1];
        stk.pop_back();
        for (int i = 1; i <= graph[temp][0]; i++)
        {
            if (visited[graph[temp][i]] == false)
            {
                stk.push_back(graph[temp][i]);
                visited[graph[temp][i]] = true;
                sum++;

                if (sum == N)
                {
                    printf("%d\n", 1);
                    return 1;
                }
            }
        }
    }
    if (sum == N)
    {
        printf("%d\n", 1);
        return 1;
    }
    else
    {
        printf("%d\n", 0);
        return 0;
    }
}

int DFS_2(std::vector<std::vector<int>> &graph, int N, int start, int end)
{
    std::vector<int> stk;
    std::vector<bool> visited(N, false);

    stk.push_back(start); // 栈实现深度优先遍历
    visited[start] = true;
    // 首先把start的除了end所有的出度压栈
    for (int i = 0; i <= graph[start][0]; i++)
    {
        if (graph[start][i] != end)
        {
            stk.push_back(graph[start][i]);
            visited[graph[start][i]] = true;
        }
    }

    while (stk.size() != 0)
    {
        int temp = stk[stk.size() - 1]; // 取栈顶元素的值
        stk.pop_back();
        for (int i = 1; i <= graph[temp][0]; i++)
        {
            if (visited[graph[temp][i]] == false)
            {
                if (end != graph[temp][i])
                {
                    stk.push_back(graph[temp][i]);
                    visited[graph[temp][i]] = true;
                }
                else if (start != temp && end == graph[temp][i])
                {
                    return 1;
                }
            }
        }
    }
    return 0;
}

int main()
{
    int N; // 节点总数
    int M; // 可能破坏的信道数
    scanf("%d%d", &N, &M);
    std::vector<std::vector<int>> graph; // 邻接表实现

    for (int i = 0; i < N; i++)
    {
        int num; // 该节点能发送的消息数
        scanf("%d", &num);
        std::vector<int> temp(num + 1);
        temp[0] = num;
        for (int j = 1; j <= num; j++)
        {
            scanf("%d", &temp[j]); // 信道i至temp[j]
        }
        graph.push_back(temp);
    }

    int flag = DFS_1(graph, N); // 函数体内已经打印过1/0

    if (flag == 0)
    {
        // 原本就不能所有节点都受到，现在损坏后也不能
        for (int i = 0; i < M; i++)
        {
            printf("%d\n", 0);
        }
    }
    else
    {
        // 原本可以收到所有节点，先只需考虑损坏信道的终点能不能收到
        for (int i = 0; i < M; i++)
        {
            int start, end; // 损坏信道的起点和终点
            scanf("%d%d", &start, &end);
            if (DFS_2(graph, N, start, end) == 1)
            {
                printf("%d\n", 1);
            }
            else
            {
                printf("%d\n", 0);
            }
        }
    }
    return 0;
}