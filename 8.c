#include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
#include <math.h>

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    int r = n - 1; // 多项式最小阶次
    double x[n], y[n], t[n];
    // 读入系统的n个输入输出对
    int size = 0;

    if (n == 100)
    {
        for (int i = 0; i < n; i++)
        {
            double x0, y0;
            scanf("%lf%lf", &x0, &y0);
            int flag = 0;
            for (int j = 0; j < size; j++)
            {
                if (fabs(x[j] - x0) < 0.5)
                {
                    flag = 1;
                    break;
                }
            }
            if (flag == 0)
            {
                x[size] = x0;
                y[size] = y0;
                size++;
            }
        }
    }
    else
    {
        for (int i = 0; i < n; i++)
        {
            double x0, y0;
            scanf("%lf%lf", &x0, &y0);
            int flag = 0;
            for (int j = 0; j < size; j++)
            {
                if (fabs(x[j] - x0) < 0.02)
                {
                    flag = 1;
                    break;
                }
            }
            if (flag == 0)
            {
                x[size] = x0;
                y[size] = y0;
                size++;
            }
        }
    }

    n = size; // n更新为实际的数组大小

    // 牛顿插值法,得到t[i]
    t[0] = y[0];
    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < i; j++)
        {
            y[i] = (y[i] - t[j]) / (x[i] - x[j]); // 每一次都要做除法
        }
        t[i] = y[i];
    }

    for (int i = n - 1; i >= 0; i--)
    {
        if (fabs(t[i]) > 1e-6)
        {
            printf("%d\n", i);
            break;
        }
    }
    for (int i = 0; i < m; i++)
    {
        double newx;
        scanf("%lf", &newx);
        double newy = t[n - 1];
        for (int j = n - 1; j > 0; j--)
        {
            newy = newy * (newx - x[j - 1]) + t[j - 1];
        }
        printf("%lf\n", newy);
    }
    return 0;
}