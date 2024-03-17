#include <stdio.h>
#include <stdlib.h>
// #include <string.h>

int main()
{
    int p, n, m;
    scanf("%d%d%d", &p, &n, &m);
    double z[n]; // z为m个列向量，每个列向量n维,所有列向量共用一个数组
    if (p == 3)
    {
        // 三对角矩阵
        double c[n - 1], b[n], a[n - 1];
        for (int i = 0; i < n - 1; i++)
        {
            scanf("%lf", &c[i]);
        }
        for (int i = 0; i < n; i++)
        {
            scanf("%lf", &b[i]);
        }
        for (int i = 0; i < n - 1; i++)
        {
            scanf("%lf", &a[i]);
        }
        // 首先数组a不变，替换数组b和c，使之成为A的LU分解
        // b[0]=b[0];
        c[0] = c[0] / b[0];
        for (int i = 1; i < n - 1; i++)
        {
            b[i] = b[i] - a[i - 1] * c[i - 1];
            c[i] = c[i] / b[i];
        }
        b[n - 1] = b[n - 1] - a[n - 2] * c[n - 2];
        // 每读入一个Z的列向量，就计算一次，输出X的列向量

        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                scanf("%lf", &z[j]);
            }
            // 操作时x，y共用一个数组，节省内存
            // 求解Ly=z
            z[0] = z[0] / b[0];
            for (int j = 1; j < n; j++)
            {
                z[j] = (z[j] - a[j - 1] * z[j - 1]) / b[j];
            }
            // 求解Ux=y
            // z[n-1]=z[n-1];
            for (int j = n - 2; j >= 0; j--)
            {
                z[j] = z[j] - c[j] * z[j + 1];
            }
            for (int j = 0; j < n; j++)
            {
                printf("%.4lf ", z[j]);
            }
            printf("\n");
        }
    }
    else if (p == 5)
    {
        // 五对角矩阵
        double e[n - 2], d[n - 1], c[n], b[n - 1], a[n - 2];
        for (int i = 0; i < n - 2; i++)
        {
            scanf("%lf", &e[i]);
        }
        for (int i = 0; i < n - 1; i++)
        {
            scanf("%lf", &d[i]);
        }
        for (int i = 0; i < n; i++)
        {
            scanf("%lf", &c[i]);
        }
        for (int i = 0; i < n - 1; i++)
        {
            scanf("%lf", &b[i]);
        }
        for (int i = 0; i < n - 2; i++)
        {
            scanf("%lf", &a[i]);
        }
        // 进行LU分解
        // b[0]=b[0]
        // c[0]=c[0];
        d[0] = d[0] / c[0];
        e[0] = e[0] / c[0];
        b[1] = b[1] - a[0] * d[0];
        c[1] = c[1] - b[0] * d[0];
        d[1] = (d[1] - b[0] * e[0]) / c[1];
        e[1] = e[1] / c[1];
        for (int i = 2; i < n - 2; i++)
        {
            b[i] = b[i] - a[i - 1] * d[i - 1];
            c[i] = c[i] - a[i - 2] * e[i - 2] - b[i - 1] * d[i - 1];
            d[i] = (d[i] - b[i - 1] * e[i - 1]) / c[i];
            e[i] = e[i] / c[i];
        }
        b[n - 2] = b[n - 2] - a[n - 3] * d[n - 3];
        c[n - 2] = c[n - 2] - a[n - 4] * e[n - 4] - b[n - 3] * d[n - 3];
        d[n - 2] = (d[n - 2] - b[n - 3] * e[n - 3]) / c[n - 2];
        c[n - 1] = c[n - 1] - a[n - 3] * e[n - 3] - b[n - 2] * d[n - 2];

        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                scanf("%lf", &z[j]);
            }
            // 主体操作部分
            // 求解Ly=z
            z[0] = z[0] / c[0];
            z[1] = (z[1] - b[0] * z[0]) / c[1];
            for (int j = 2; j < n; j++)
            {
                z[j] = (z[j] - b[j - 1] * z[j - 1] - a[j - 2] * z[j - 2]) / c[j];
            }
            // 求解Ux=y
            // z[n-1]=z[n-1];
            z[n - 2] = z[n - 2] - d[n - 2] * z[n - 1];
            for (int j = n - 3; j >= 0; j--)
            {
                z[j] = z[j] - d[j] * z[j + 1] - e[j] * z[j + 2];
            }
            for (int j = 0; j < n; j++)
            {
                printf("%.4lf ", z[j]);
            }
            printf("\n");
        }
    }
    return 0;
}