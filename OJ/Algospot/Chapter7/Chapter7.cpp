#include <iostream>
#include <string>
#include <vector>

using namespace std;

int fastSum(int n)
{
  if (n == 0)
    return 0;
  if (n % 2 != 0)
    return n + fastSum(n - 1);

  return (2 * fastSum(n / 2)) + (n * n / 4);
}

int main()
{
  cout << fastSum(11) << endl;
  return 0;
}