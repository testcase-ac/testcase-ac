#include <bits/stdc++.h>
using namespace std;

int d[32769][200][5];
int nc(int n, int cv, int k) {
  if (n == 0) return 1;
  if (k == 0 || cv == 0) return 0;

  if (d[n][cv][k] == -1) {
    int ans = nc(n, cv - 1, k);
    if (cv * cv <= n) ans += nc(n - cv * cv, cv, k - 1);
    d[n][cv][k] = ans;
  }
  return d[n][cv][k];
}

int main() {
  int n;
  memset(d, -1, sizeof(d));

  while (1) {
    cin >> n;
    if (!n) break;

    cout << nc(n, floor(sqrt(n)), 4) << '\n';
  }
}
