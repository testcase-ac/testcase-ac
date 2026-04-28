#include <bits/stdc++.h>
#define TIMES(n) for (int i = 0; i < n; i++)
using namespace std;

int sticks[100];
int main() {
  int x1, y1, z1, x2, y2, z2, n, k;
  cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2 >> n;

  TIMES(n) cin >> sticks[i];
  sort(sticks, sticks + n);
  double dist = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1) + (z2 - z1) * (z2 - z1));
  int ldist = accumulate(sticks, sticks + n - 1, 0);
  int mdist = sticks[n - 1];

  cout << (mdist - dist <= ldist && mdist + ldist >= dist ? "YES\n" : "NO\n");
}
