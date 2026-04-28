#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int x[500];

void solve() {
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> x[i];

  if (n <= 4) cout << "YES";
  else {
    int a = -x[0] + 3 * x[1] - 3 * x[2] + x[3];
    int b = 9 * x[0] - 24 * x[1] + 21 * x[2] - 6 * x[3];
    int c = -26 * x[0] + 57 * x[1] - 42 * x[2] + 11 * x[3];
    int d = 24 * x[0] - 36 * x[1] + 24 * x[2] - 6 * x[3];

    bool able = true;
    for (int i = 5; i <= n; i++) {
      if (a * i * i * i + b * i * i + c * i + d != 6 * x[i - 1]) able = false;
    }
    if (able) cout << "YES";
    else cout << "NO";
  }
  cout << '\n';
}

int main() {
  fast_io();

  int t;
  cin >> t;
  while (t--) solve();
}
