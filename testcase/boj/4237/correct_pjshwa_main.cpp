#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 30000;
int A[MAX];

void solve() {
  int n, x;
  cin >> n >> x;

  int ans = 1;
  for (int i = 1; i < n; i++) {
    int y; cin >> y;
    if (ans & 1) {
      if (y < x) ans++;
    }
    else {
      if (y > x) ans++;
    }
    x = y;
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
