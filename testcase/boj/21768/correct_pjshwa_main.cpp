#include <bits/stdc++.h>
using namespace std;

int a[1 << 20];
int main() {
  int n;
  cin >> n;
  for (int i = 0; i < (1 << n); i++) cin >> a[i];

  for (int i = 0; i < (1 << n); i++) {
    for (int j = 0; j < n; j++) {
      for (int k = 0; k < n; k++) {
        int x = 1 << j, y = 1 << k;
        if (x == y || (i & x) || (i & y)) continue;
        if (a[i + x] - a[i] >= a[i + x + y] - a[i + y]) continue;
        cout << i + x << ' ' << i + y;
        return 0;
      }
    }
  }
  cout << -1;
}
