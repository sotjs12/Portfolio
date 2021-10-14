#include <iostream>
#include <vector>
#include <string>
#include <cstring>

using namespace std;

int C;

string solve(string::iterator &it)
{
  char head = *it;
  ++it;

  if (head == 'b' || head == 'w')
    return string(1, head);

  string upperLeft = solve(it);
  string upperRight = solve(it);
  string lowerLeft = solve(it);
  string lowerRight = solve(it);

  return "x" + lowerLeft + lowerRight + upperLeft + upperRight;
}

int main()
{
  freopen("QUADTREE.txt", "r", stdin);
  cin >> C;
  while (C--)
  {
    string in;
    cin >> in;
    string::iterator it = in.begin();
    cout << solve(it) << endl;
  }

  return 0;
}