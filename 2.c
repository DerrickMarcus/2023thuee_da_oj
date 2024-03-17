#include <stdio.h>

int main()
{
    int N;
    int cmd1, cmd2, cmd3;
    scanf("%d", &N);
    int queue_next[100001] = {1, 0};
    int queue_prev[100001] = {1, 0};
    for (int i = 2; i < 100001; i++)
    {
        queue_next[i] = queue_prev[i] = -1;
    }
    for (int i = 0; i < N; i++)
    {
        scanf("%d", &cmd1);
        switch (cmd1)
        {
        case 1:
            scanf("%d%d", &cmd2, &cmd3);
            queue_next[cmd3] = queue_next[cmd2];
            queue_prev[queue_next[cmd2]] = cmd3;
            queue_next[cmd2] = cmd3;
            queue_prev[cmd3] = cmd2;
            break;
        case 2:
            scanf("%d", &cmd2);
            printf("%d\n", queue_next[cmd2]);
            break;
        case 3:
            scanf("%d", &cmd2);
            queue_prev[queue_next[cmd2]] = queue_prev[cmd2];
            queue_next[queue_prev[cmd2]] = queue_next[cmd2];
            queue_next[cmd2] = queue_prev[cmd2] = -1;

            break;
        }
    }
    int i = 0;
    while (queue_next[i])
    {
        printf("%d\n", queue_next[i]);
        i = queue_next[i];
    }
    return 0;
}