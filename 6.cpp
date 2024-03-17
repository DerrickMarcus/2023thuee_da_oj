#include <cstdio>
#include <vector>
#include <algorithm>

long long search(std::vector<int> &vec, int height, int H)
{
    long long min = 0, max = vec.size() - 1;
    long long i = 0;
    for (i = 0; i < vec.size(); i++)
    {
        if (vec[i] >= height - H)
        {
            break;
        }
    }
    min = i;
    for (i = vec.size() - 1; i >= 0; i--)
    {
        if (vec[i] - H <= height)
        {
            break;
        }
    }
    max = i;
    return max - min + 1;
}

int main()
{
    int M, K, H;
    long long count = 0;
    scanf("%d%d%d", &M, &K, &H);
    if (K < M - 1)
    {
        std::vector<int> stair;
        int height = 0;
        std::vector<int> dele(M - K, 0);
        for (int i = 0; i < M; i++)
        {
            scanf("%d", &height);
            count += search(stair, height, H);
            if (i < M - K)
            {
                dele[i] = height;
            }
            if (i >= K)
            {
                // 先删除一个元素
                stair.erase(remove(stair.begin(), stair.end(), dele[i - K]), stair.end());
            }
            // 二分插入新的元素
            int left = 0, right = stair.size() - 1;
            int mid;
            while (left <= right)
            {
                mid = left + (right - left) / 2;
                if (height < stair[mid])
                {
                    right = mid - 1;
                }
                else
                {
                    left = mid + 1;
                }
            }
            stair.insert(stair.begin() + left, height);
        }
    }
    else
    {
        // K>=M-1，全区间都可能跳跃
        std::vector<int> stair;
        int height = 0;
        for (int i = 0; i < M; i++)
        {
            scanf("%d", &height);
            count += search(stair, height, H);
            //  二分插入新的元素
            int left = 0, right = stair.size() - 1;
            int mid;
            while (left <= right)
            {
                mid = left + (right - left) / 2;
                if (height < stair[mid])
                {
                    right = mid - 1;
                }
                else
                {
                    left = mid + 1;
                }
            }
            stair.insert(stair.begin() + left, height);
        }
    }
    printf("%lld", count);
    return 0;
}