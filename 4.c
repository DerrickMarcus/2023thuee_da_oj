#include <stdio.h>

typedef struct
{
    long long start; // 某一层的头节点
    long long end;   // 某一层的尾节点
} Floor;

typedef struct
{
    long long data; // 某个目标点
    int floor;      // 该目标点在第几层
} Node;

int main()
{
    int N, M;                        // 缺损点数目和目标点数目
    long long defect[100];           // 记录缺损点及其所在层数
    long long df_fl[134][101] = {0}; // 记录每一层缺损点及其个数
    Node target[100];                // 记录目标点及其所在层数
    Floor floor[134];                // 经计算可得缺损树最多133层，第0层为1
    floor[0].start = floor[0].end = 1;

    scanf("%d%d", &N, &M);
    for (int i = 0; i < N; i++)
    {
        scanf("%lld", &defect[i]);
    }
    for (int i = 0; i < M; i++)
    {
        scanf("%lld", &target[i].data);
    }

    if (defect[0] == 1) // 如果根节点1缺损，那么后续全都不存在了
    {
        for (int i = 0; i < M; i++)
        {
            if (target[i].data == 1)
                printf("%d\n", 1);
            else
                printf("%d\n", 0);
        }
        return 0;
    }

    // 开始构造缺损树
    int cur_fl = 1; // 当前层数
    int df_num = 0; // 当前层的所有缺损点数
    int flag_d = 0; // 当前将要遇到哪个缺损点defect[flag_d]
    int flag_t = 0; // 当前将要遇到哪个目标点target[flag_t].data
    long long last_nd;

    if (target[0].data == 1)
    {
        target[0].floor = 0;
        flag_t++;
    }

    for (cur_fl = 1; cur_fl < 134; cur_fl++)
    {
        floor[cur_fl].start = floor[cur_fl - 1].end + 1;                                                              // 确定起点
        floor[cur_fl].end = floor[cur_fl].start + (floor[cur_fl - 1].end - floor[cur_fl - 1].start - df_num) * 2 + 1; // 确定终点
        df_num = 0;                                                                                                   // 重置这一行的缺损点数

        int i;
        for (i = flag_d; i < N; i++)
        {
            // 判断这一行有几个缺损点
            if (floor[cur_fl].start <= defect[i] && defect[i] <= floor[cur_fl].end)
            {
                df_fl[cur_fl][i - flag_d + 1] = defect[i];
                df_num++;
            }
            else
                break;
        }
        // 此时，这一行的缺损点数目为df_num
        df_fl[cur_fl][0] = df_num; // 这一行的缺损点个数存放在数组第一位
        flag_d = i;

        int j;
        for (j = flag_t; j < M; j++)
        {
            // 记录该层所有目标点的层数
            if (floor[cur_fl].start <= target[j].data && target[j].data <= floor[cur_fl].end)
            {
                target[j].floor = cur_fl;
            }
            else
                break;
        }
        flag_t = j;

        if (floor[cur_fl].end >= target[M - 1].data || floor[cur_fl].end - floor[cur_fl].start + 1 == df_num)
        {
            // 如果已经构造到最后一个目标点，或者这一行全是缺损点，停止构造
            last_nd = floor[cur_fl].end; // 记录构造到的最后一个节点
            break;
        }
    }

    // 开始搜索回到根结点的路径
    for (int i = 0; i < M; i++)
    {
        if (target[i].data > last_nd)
        {
            printf("%d\n", 0);
            continue;
        } // 路径不存在的情况，直接输出0

        long long temp[134] = {1};
        // 该目标点层数为target[i].floor
        // 在df_fl[floor]中还要判断可能碰到的缺损点
        int cur_fl = target[i].floor;      // 当前层数
        long long new_ta = target[i].data; // 当前节点
        while (cur_fl > 0)
        {
            temp[cur_fl] = new_ta;
            long long cnt = (new_ta - floor[cur_fl].start) / 2;
            int flag = 0;
            for (int j = 1; j <= df_fl[cur_fl - 1][0]; j++)
            {
                if (cnt + j <= df_fl[cur_fl - 1][j] - floor[cur_fl - 1].start)
                {
                    break;
                }
                else
                {
                    flag = j;
                }
            }
            new_ta = floor[cur_fl - 1].start + cnt + flag;
            cur_fl--;
        }
        printf("%d", 1); // 最先输出根节点
        for (int j = 1; j <= target[i].floor; j++)
        {
            printf(" %lld", temp[j]);
        }
        printf("\n");
    }

    return 0;
}