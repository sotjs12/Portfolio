#include <iostream>
#include <vector>
#include <string>
#include <cstring>

using namespace std;

int C, N, IN;
const int MAX_X = 100, MAX_Y = 100;
int board[MAX_Y + 1][MAX_X + 1];
int dp[MAX_Y + 1][MAX_X + 1];

int solve(int y, int x)
{
  if (y == N && x == N)
    return 1;
  if (y > N || x > N)
    return 0;

  int &ret = dp[y][x];
  if (ret != -1)
    return ret;

  return ret = solve(y + board[y][x], x) || solve(y, x + board[y][x]);
}

int main()
{
  freopen("JUMPGAME.txt", "r", stdin);
  cin >> C;
  while (C--)
  {
    memset(dp, -1, sizeof(dp));
    memset(board, -1, sizeof(board));

    cin >> N;
    for (int y = 0; y < N; ++y)
      for (int x = 0; x < N; ++x)
      {
        cin >> IN;
        board[y][x] = IN;
      }
    N = N - 1;

    cout << (solve(0, 0) ? "YES" : "NO") << endl;
  }

  return 0;
}