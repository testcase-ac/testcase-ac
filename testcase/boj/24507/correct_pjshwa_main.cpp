#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int n;
  cin >> n;
  if (n % 4 == 2 || n % 4 == 3) return cout << "No\n", void();

  if (n == 4) return cout << "Yes\n1 2 1 3 2 0 0 3\n", void();
  if (n == 5) return cout << "Yes\n2 4 1 2 1 3 4 0 0 3\n", void();

  cout << "Yes\n";
  int a[2 * n + 1];
  memset(a, -1, sizeof(a));

  int k = n / 4;
  if (n % 4 == 0) {
    for (int r = 0; r <= 2 * k - 1; r++) {
      int s = 4 * k + r, e = 8 * k - r;
      a[s] = a[e] = e - s;
    }
    for (int r = 0; r <= 0; r++) {
      int s = 2 * k + 1, e = 6 * k;
      a[s] = a[e] = e - s;
    }
    for (int r = 0; r <= 0; r++) {
      int s = 2 * k, e = 4 * k - 1;
      a[s] = a[e] = e - s;
    }
    for (int r = 1; r <= k - 1; r++) {
      int s = r, e = 4 * k - 1 - r;
      a[s] = a[e] = e - s;
    }
    for (int r = 0; r <= 0; r++) {
      int s = k, e = k + 1;
      a[s] = a[e] = e - s;
    }
    for (int r = 0; r <= k - 3; r++) {
      int s = k + 2 + r, e = 3 * k - 1 - r;
      a[s] = a[e] = e - s;
    }
  }
  else {
    for (int r = 0; r <= 2 * k - 1; r++) {
      int s = 4 * k + 2 + r, e = 8 * k + 2 - r;
      a[s] = a[e] = e - s;
    }
    for (int r = 0; r <= 0; r++) {
      int s = 2 * k + 1, e = 6 * k + 2;
      a[s] = a[e] = e - s;
    }
    for (int r = 0; r <= 0; r++) {
      int s = 2 * k + 2, e = 4 * k + 1;
      a[s] = a[e] = e - s;
    }
    for (int r = 1; r <= k; r++) {
      int s = r, e = 4 * k + 1 - r;
      a[s] = a[e] = e - s;
    }
    for (int r = 0; r <= 0; r++) {
      int s = k + 1, e = k + 2;
      a[s] = a[e] = e - s;
    }
    for (int r = 1; r <= k - 2; r++) {
      int s = k + 2 + r, e = 3 * k + 1 - r;
      a[s] = a[e] = e - s;
    }
  }

  for (int i = 1; i <= 2 * n; i++) cout << a[i] - 1 << " ";
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
