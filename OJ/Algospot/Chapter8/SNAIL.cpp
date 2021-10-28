#include <iostream>

using namespace std;

const int MAX = 1000; 
int height, day;
double cache[MAX][2 * MAX]; 

double climb(int passed, int climbed)
{
  if (passed == day)
    return climbed >= height ? 1 : 0;

  double &result = cache[passed][climbed];
  if (result != -1.0)
    return result;

  return result = (0.25 * climb(passed + 1, climbed + 1)) + (0.75 * climb(passed + 1, climbed + 2));
}

int main(void)
{
  int test_case;
  cin >> test_case;

  if (test_case > 50 || test_case < 1)
    exit(-1);

  for (int i = 0; i < test_case; i++)
  {
    cin >> height >> day;

    if (height < 1 || height > 1000 || day < 1 || day > 1000)
      exit(-1);
    for (int i = 0; i < 1000; i++)
      for (int j = 0; j < 2000; j++)
        cache[i][j] = -1.0;

    cout.precision(11);
    cout << climb(0, 0) << endl
         << endl;
  }

  return 0;
}