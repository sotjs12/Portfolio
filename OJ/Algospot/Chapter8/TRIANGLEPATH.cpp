#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>

using namespace std;

int C, N;
const int MAX_P = 100, MAX_S = 100;
int board[MAX_P + 1][MAX_S + 1];
int dp[MAX_P + 1][MAX_S + 1];

int solve(int y, int x)
{
  if (y == N - 1)
    return board[y][x];

  int &ret = dp[y][x];
  if (ret != -1)
    return ret;

  return ret = max(solve(y + 1, x), solve(y + 1, x + 1)) + board[y][x];
}

int main()
{
  freopen("TRIANGLEPATH.txt", "r", stdin);
  cin >> C;
  while (C--)
  {
    memset(board, -1, sizeof(board));
    memset(dp, -1, sizeof(dp));

    cin >> N;
    for (int y = 0; y < N; ++y)
      for (int x = 0; x <= y; ++x)
        cin >> board[y][x];

    cout << solve(0, 0) << endl;
  }
  return 0;
}