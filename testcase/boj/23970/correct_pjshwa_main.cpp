#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e4;
int a[MAX], b[MAX], c[MAX];

void solve() {
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> a[i];
  for (int i = 0; i < n; i++) cin >> b[i];

  int d = n - 1;
  while (d >= 0 && a[d] == b[d]) d--;
  if (d == -1) return cout << "1\n", void();

  for (int i = n - 1; i > 0; i--) {
    for (int j = 0; j < i; j++) {
      if (a[j] > a[j + 1]) {
        swap(a[j], a[j + 1]);
        if (j > d) return cout << "0\n", void();
      }
      while (d >= 0 && a[d] == b[d]) d--;
      if (d == -1) return cout << "1\n", void();
    }
  }

  cout << "0\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
