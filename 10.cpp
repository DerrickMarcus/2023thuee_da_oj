#include <cstdio>
#include <vector>
#include <algorithm>
// #include <cstdlib>
// #include <cmath>

int main(int argc, const char *argv[])
{
    // n个张量，每个都是K维
    // n<2048,K<32
    int n, K;
    scanf("%d%d", &n, &K);
    std::vector<std::vector<int>> tensor(n, std::vector<int>(K));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < K; j++)
        {
            scanf("%d", &tensor[i][j]);
        }
    }

    // dp[i][j]表示从第i个张量到第j个张量运算的最小乘法次数，最后问题的解就是dp[0][n-1]
    // i<=j，这是一个上三角矩阵
    // 边界条件dp[i][i]=0;
    // 状态转移方程dp[i][j]=min(dp[i][k]+dp[k+1][j]+cost(ikj)),i<=k<j
    // cost(ikj)为被第k个张量分割的前后两部分相乘的乘法次数
    std::vector<std::vector<int>> dp(n, std::vector<int>(n));
    for (int i = 0; i < n; i++)
    {
        dp[i][i] = 0;
    }
    for (int j = 1; j < n; j++)
    {
        // 对于第j列，从下向上求解
        // 预先计算一部分前K-2维相乘所需要的乘法次数
        std::vector<int> temp = tensor[j];
        for (int i = j - 1; i >= 0; i--)
        {
            // 求解dp[i][j]
            int result = tensor[i][K - 2] * tensor[j][K - 1];
            for (int x = 0; x < K - 2; x++)
            {
                // i每向前移一位，更新张量各个维度的最大值
                temp[x] = std::max(temp[x], tensor[i][x]);
                result *= temp[x];
            }

            int min_times = 0x7fffffff;
            for (int k = i; k < j; k++)
            {
                min_times = std::min(min_times, dp[i][k] + dp[k + 1][j] + result * tensor[k][K - 1]);
            }
            dp[i][j] = min_times;
        }
    }

    printf("%d", dp[0][n - 1]);

    return 0;
}
