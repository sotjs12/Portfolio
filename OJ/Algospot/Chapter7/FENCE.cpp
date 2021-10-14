#include <iostream>
#include <vector>
#include <string>
#include <cstring>

using namespace std;

int C, N, IN;
vector<int> heights;

int solve(int left, int right)
{
  if (left == right)
    return heights[left];

  int mid = (left + right) / 2;
  int lo = mid, hi = mid + 1;
  int ret = max(solve(left, mid), solve(mid + 1, right));

  int height = min(heights[mid], heights[mid + 1]);
  ret = max(ret, height * 2);

  while (left < lo || hi < right)
  {
    if (hi < right && (lo == left || heights[lo - 1] < heights[hi + 1]))
    {
      hi++;
      height = min(height, heights[hi]);
    }
    else
    {
      lo--;
      height = min(height, heights[lo]);
    }
    ret = max(ret, height * (hi - lo + 1));
  }

  return ret;
}

int main()
{
  freopen("FENCE.txt", "r", stdin);
  cin >> C;
  while (C--)
  {
    heights.clear();
    cin >> N;
    while (N-- && cin >> IN)
      heights.push_back(IN);

    cout << solve(0, heights.size() - 1) << endl;
  }

  return 0;
}