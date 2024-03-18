# OJ7:带限矩阵方程组求解

## 【问题描述】

考虑如下的带限矩阵方程组：
$$
AX=Z
$$
其中![img](http://oj.ee.tsinghua.edu.cn/media/ckeditor_uploads/2023/11/23/2023-11-23-230051.png)为带限的三对角或五对角矩阵，若为三对角矩阵则有以下形式：

![img](http://oj.ee.tsinghua.edu.cn/media/ckeditor_uploads/2023/11/23/2023-11-23-230003.png)

若为五对角矩阵则有以下形式：

![img](http://oj.ee.tsinghua.edu.cn/media/ckeditor_uploads/2023/11/23/2023-11-23-230031.png)

![img](http://oj.ee.tsinghua.edu.cn/media/ckeditor_uploads/2023/11/26/2023-11-26-140122.png)由m个列向量构成。现在给定非奇异矩阵A和矩阵Z，求解矩阵X。



## 【输入格式】

第1行输入p，表示矩阵A中存在非零元素的对角线的条数，p为3或5。

第2行输入n和m，表示矩阵A的维数和矩阵Z的维数。其中n不超过10000，m不超过500.

第3行到第p+2行，按照从矩阵A的最上方的对角线到最下方的对角线的顺序依次输入各对角线的元素值。

即对于三对角矩阵，第3行输入![img](http://oj.ee.tsinghua.edu.cn/media/ckeditor_uploads/2023/11/23/2023-11-23-230340.png)，第4行输入![img](http://oj.ee.tsinghua.edu.cn/media/ckeditor_uploads/2023/11/23/2023-11-23-230358.png)，第5行输入![img](http://oj.ee.tsinghua.edu.cn/media/ckeditor_uploads/2023/11/23/2023-11-23-230423.png)；

对于五对角矩阵， 第3行输入![img](http://oj.ee.tsinghua.edu.cn/media/ckeditor_uploads/2023/11/23/2023-11-23-230617.png)，第4行输入![img](http://oj.ee.tsinghua.edu.cn/media/ckeditor_uploads/2023/11/23/2023-11-23-230643.png)，第5行输入![img](http://oj.ee.tsinghua.edu.cn/media/ckeditor_uploads/2023/11/23/2023-11-23-230700.png)，第6行输入![img](http://oj.ee.tsinghua.edu.cn/media/ckeditor_uploads/2023/11/23/2023-11-23-230712.png)，第7行输入![img](http://oj.ee.tsinghua.edu.cn/media/ckeditor_uploads/2023/11/23/2023-11-23-230731.png)。

最后m行每行输入n个浮点数，为别为矩阵Z的第m列向量zm的n个元素值，即

![img](http://oj.ee.tsinghua.edu.cn/media/ckeditor_uploads/2023/11/26/2023-11-26-140724.png)



## 【输出格式】

输出共m行，每行为n个浮点数，分别为矩阵X的每一列的各个元素值，每个元素值结果四舍五入保留4位小数。



## 【输入样例】

```
3
3 2
44 62 
44 43 30 
3 34 
27 63 53 
14 52 19
```

3
3 2
44 62 
44 43 30 
3 34 
27 63 53 
14 52 19



## 【输出样例】

```
-0.9846 1.5983 -0.0447 
0.7073 -0.3892 1.0744
```

-0.9846 1.5983 -0.0447 
0.7073 -0.3892 1.0744



## 【时间、内存限制】

时间1000ms

内存1500KB



## 【提示】

计算带限矩阵LU分解后元素间的递推表达式。



## 【思路】

1. 矩阵A作用于X的第i个列向量，得到Z的第i个列向量。
   $$
   AX=Z\\
   Ax_i=z_i
   $$
   因此可以每读入一个Z的列向量，计算出X对应的列向量，进行输出。

2. 对矩阵A进行LU分解：
   $$
   A=LU
   $$
   

   LU分解如下：
   $$
   \begin{bmatrix}
   b_1 & c_1 \\
   a_2 & b_2 & c_2\\
   & \ddots & \ddots & \ddots\\
   & & a_{n-1} & b_{n-1} & c_{n-1}\\
   & & & a_n & b_n
   \end{bmatrix}
   =
   \begin{bmatrix}
   \beta_1\\
   a_2 & \beta_2\\
   & \ddots & \ddots\\
   & & a_{n-1} & \beta_{n-1}\\
   & & & a_n & \beta_n
   \end{bmatrix}
   \begin{bmatrix}
   1 & \gamma_1 \\
   & 1 & \gamma_2\\
   & & \ddots & \ddots\\
   & & & 1 & \gamma_{n-1}\\
   & & & & 1
   \end{bmatrix}
   $$
   递推公式为：
   $$
   \beta_1=b_1,\ \gamma_1=\frac{c_1}{b_1}\\
   \beta_i=b_i-a_i\gamma_{i-1},\ \gamma_i=\frac{c_i}{\beta_i}
   $$

   因此只需将数组`b[n]`替换为`β[n]`，将数组`c[n-1]`替换为`γ[n-1]`，即可求出LU分解。

   先通过前向回代，求解：
   $$
   Ly=z
   $$
   再通过后向回代，求解：
   $$
   Ux=y
   $$
   ![image-20231212145422615](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20231212145422615.png)

   上述方法参见教程：[三对角矩阵的LU分解](https://blog.csdn.net/Giannis_34/article/details/107872239 "CSDN博客：追赶法求三对角矩阵、LU分解")

3. 对于五对角矩阵，可以采取大致相同的思路，是不过稍微复杂一点：

   LU分解如下：
   $$
   \begin{bmatrix}
   c_1 & d_1 & e_1\\
   b_2 & c_2 & d_2 & e_2\\
   a_3 & b_3 & c_3 & d_3 & e_3\\
   & a_4 & b_4 & c_4 & d_4 & e_4\\
   & & \ddots & \ddots & \ddots & \ddots & \ddots\\
   & & & \ddots & \ddots & \ddots & \ddots & \ddots\\
   & & & & a_{n-2} & b_{n-2} & c_{n-2} & d_{n-2} & e_{n-2}\\
   & & & & & a_{n-1} & b_{n-1} & c_{n-1} & d_{n-1}\\
   & &  && & & a_n & b_n & c_n\\
   \end{bmatrix}
   =
   $$
   ![img](http://oj.ee.tsinghua.edu.cn/media/ckeditor_uploads/2023/11/23/2023-11-23-230031.png)

   ![屏幕截图 2023-12-12 195445](D:\ASUS\Pictures\Saved Pictures\屏幕截图 2023-12-12 195445.png)

   

![屏幕截图 2023-12-12 195500](D:\ASUS\Pictures\Saved Pictures\屏幕截图 2023-12-12 195500.png)

![屏幕截图 2023-12-12 195530](D:\ASUS\Pictures\Saved Pictures\屏幕截图 2023-12-12 195530.png)

上述的方法参见教程：[五对角追赶发求解线性方程组](https://blog.csdn.net/wxkhturfun/article/details/125023717)。



## 【代码（C）】

```c
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
```



最后附上作者的通过图片：

![屏幕截图 2023-12-12 195139](D:\ASUS\Pictures\Saved Pictures\屏幕截图 2023-12-12 195139.png)
