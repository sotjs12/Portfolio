#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

const int INF = 9999, SWITCHE_CNT = 10, CLOCK_CNT = 16;
const char switches[SWITCHE_CNT][CLOCK_CNT + 1] = {
    "xxx.............",
    "...x...x.x.x....",
    "....x.....x...xx",
    "x...xxxx........",
    "......xxx.x.x...",
    "x.x...........xx",
    "...x..........xx",
    "....xx.x......xx",
    ".xxxxx..........",
    "...xxx...x...x..",
};
int C;
vector<int> clocks;

void push(int s)
{
  for (int i = 0; i < CLOCK_CNT; ++i)
  {
    if (switches[s][i] == 'x')
    {
      clocks[i] += 3;
      if (clocks[i] == 15)
        clocks[i] = 3;
    }
  }
}
bool isSolved()
{
  for (int i = 0; i < CLOCK_CNT; ++i)
  {
    if (clocks[i] != 12)
      return false;
  }
  return true;
}
int solve(int s)
{
  if (s == SWITCHE_CNT)
  {
    if (isSolved())
      return 0;
    else
      return INF;
  }

  int ret = INF;
  for (int i = 0; i < 4; ++i)
  {
    ret = min(solve(s + 1) + i, ret);
    push(s);
  }

  return ret;
}

int main()
{
  freopen("C_6_4.txt", "r", stdin);
  cin >> C;
  while (C--)
  {
    clocks.clear();
    for (int i = 0, input; i < CLOCK_CNT; ++i)
    {
      cin >> input;
      clocks.push_back(input);
    }
    int result = solve(0);
    result = (result == INF) ? -1 : result;
    cout << result << endl;
  }

  return 0;
}