#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

int n;
bool areFriend[10][10];
bool taken[10];

int solve()
{
    int from = -1;
    for (int i = 0; i < n; ++i)
    {
        if (!taken[i])
        {
            from = i;
            break;
        }
    }
    if (from == -1)
        return 1;

    int ret = 0;
    for (int to = from + 1; to < n; ++to)
    {
        if (!taken[to] && areFriend[from][to])
        {
            taken[from] = taken[to] = true;
            ret += solve();
            taken[from] = taken[to] = false;
        }
    }

    return ret;
}

void PICNIC()
{
    int test = 0;

    cin >> test;

    while (test--)
    {
        memset(taken, false, sizeof(taken));
        memset(areFriend, false, sizeof(areFriend));

        int student, pairCnt, y, x;

        cin >> n >> pairCnt;

        while (pairCnt--)
        {
            cin >> y >> x;
            areFriend[y][x] = areFriend[x][y] = true;
        }

        cout << solve() << endl;
    }
}

int main()
{
    PICNIC();
    return 0;
}