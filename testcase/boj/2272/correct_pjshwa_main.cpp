#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e6;
int a[MAX], b[MAX];

void solve() {
  int n, m;
  cin >> n >> m;
  for (int i = 0; i < n; i++) cin >> a[i];

  for (int i = 1; i <= m; i <<= 1) {
    if (i & m) {
      for (int j = 0; j < n; j++) b[j] = a[j] ^ a[(i + j) % n];
      for (int j = 0; j < n; j++) a[j] = b[j];
    }
  }

  for (int i = 0; i < n; i++) cout << a[i] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
