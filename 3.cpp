#include <cstdio>
#include <stack>
struct Soldier
{
    int force;
    int repeat;
};

int main()
{
    int N;
    long result = 0;
    scanf("%d", &N);
    std::stack<Soldier> soldier;
    int Force = 0;
    scanf("%d", &Force);
    Soldier s;
    s.force = Force;
    s.repeat = 1;
    soldier.push(s);
    // 第一个士兵首先入栈

    for (int i = 1; i < N; i++)
    {
        scanf("%d", &Force);

        if (soldier.top().force > Force)
        {
            result++;
            s.force = Force;
            s.repeat = 1;
            soldier.push(s);
        }

        else
        {
            int flag = 0; // 记录遇到和自己相同的次数
            while (!soldier.empty() && soldier.top().force <= Force)
            {
                if (soldier.top().force == Force)
                {
                    flag = soldier.top().repeat;
                    // 时刻记录当前弹出的武力值是否和自己相等。
                }
                result += soldier.top().repeat;
                soldier.pop();
            }
            if (!soldier.empty())
            {
                result++; // 此时栈不为空说明前面还有比自己更大的
            };
            s.force = Force;
            s.repeat = flag + 1;
            soldier.push(s);
        }
    }

    printf("%ld", result);
    return 0;
}