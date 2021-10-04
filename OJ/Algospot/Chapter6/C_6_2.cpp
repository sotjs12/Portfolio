#include <iostream>
#include <string>
#include <cstring>
#include <vector>

using namespace std;

//BOARDCOVER

int H, W;
int dp[20][20];
int board[20][20];
int coverType[4][3][2] = {
    {{0, 0}, {1, 0}, {0, 1}},
    {{0, 0}, {0, 1}, {1, 1}},
    {{0, 0}, {1, 0}, {1, 1}},
    {{0, 0}, {1, 0}, {1, -1}}};

vector<int> blockX, blockY;

bool visitable(int y, int x, int type)
{
    for (int i = 0; i < 3; ++i)
    {
        int ny = y + coverType[type][i][0];
        int nx = x + coverType[type][i][1];
        if (ny < 0 || nx < 0 || ny >= H || nx >= W || board[ny][nx] == 0)
            return false;
    }

    return true;
}
void visit(int y, int x, int type, int mode)
{
    for (int i = 0; i < 3; ++i)
    {
        int ny = y + coverType[type][i][0];
        int nx = x + coverType[type][i][1];
        board[ny][nx] = mode;
    }
}

int solve()
{
    int y = -1, x = -1, ret = 0;
    bool find = false;

    for (int i = 0; i < blockY.size(); ++i)
    {
        y = blockY[i];
        x = blockX[i];
        if (board[y][x] == 1)
        {
            find = true;
            break;
        }
    }
    if (!find)
        return 1;

    for (int i = 0; i < 4; ++i)
    {
        if (visitable(y, x, i))
        {
            visit(y, x, i, 0);
            ret += solve();
            visit(y, x, i, 1);
        }
    }
    return ret;
}

int main()
{
    int C, result;
    string line;

    freopen("C_6_2.txt", "r", stdin);

    cin >> C;
    while (C--)
    {
        memset(board, -1, sizeof(board));
        memset(dp, -1, sizeof(dp));
        blockX.clear();
        blockY.clear();
        result = 0;

        cin >> H >> W;

        for (int y = 0; y < H; ++y)
        {
            cin >> line;
            for (int x = 0; x < W; ++x)
            {
                board[y][x] = (line[x] == '#') ? 0 : 1;
                if (board[y][x] == 1)
                {
                    blockY.push_back(y);
                    blockX.push_back(x);
                }
            }
        }

        if (blockY.size() % 3 == 0)
        {
            result = solve();
        }

        cout << solve() << endl;
    }

    return 0;
}