#include <stdio.h>

int main(int argc, const char *argv[])
{
    int N, input, result = 0;
    int arr[32] = {0};
    scanf("%d", &N);
    for (int i = 0; i < 3 * N - 1; i++)
    {
        scanf("%d", &input);
        for (int j = 0; j < 32; j++)
        {
            arr[j] += (input & (1 << j)) ? 1 : 0;
        }
    }
    for (int i = 0; i < 32; i++)
    {
        result += ((arr[i] % 3) / 2) << i;
    }
    printf("%d", result);
    return 0;
}