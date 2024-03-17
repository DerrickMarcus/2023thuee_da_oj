#include <stdio.h>

typedef struct
{
    int force;
    int repeat;
} Soldier;

int main()
{
    int N;
    long result = 0;
    scanf("%d", &N);
    Soldier soldier[500000];
    int Force = 0;
    int top = 0; // 记录栈顶位置
    scanf("%d", &Force);
    soldier[0].force = Force;
    soldier[0].repeat = 1;
    // 第一个士兵首先入栈

    for (int i = 1; i < N; i++)
    {
        scanf("%d", &Force);

        if (soldier[top].force > Force)
        {
            result++;
            top++;
            soldier[top].force = Force;
            soldier[top].repeat = 1;
        }

        else
        {
            int flag = 0; // 记录遇到和自己相同的次数
            while (top >= 0 && soldier[top].force <= Force)
            {
                if (soldier[top].force == Force)
                {
                    flag = soldier[top].repeat;
                    // 时刻记录当前弹出士兵的武力值是否和自己相等。
                }
                result += soldier[top].repeat;
                soldier[top].force = 0;
                soldier[top].repeat = 0;
                top--;
            }
            if (top >= 0)
            {
                result++; // 此时栈不为空说明前面还有比自己更大的
            }
            top++;
            soldier[top].force = Force;
            soldier[top].repeat = flag + 1;
        }
    }

    printf("%ld", result);
    return 0;
}
