#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int X, Y, A[5]; cin >> X >> Y;
  for (int i = 0; i < 5; ++i) cin >> A[i];

  for (int s = 0; s < 32; ++s) {
    int sum = 0;
    for (int i = 0; i < 5; ++i) {
      if (s & (1 << i)) sum += A[i];
    }
    if (sum >= X && sum <= Y) {
      cout << "YES\n";
      return;
    }
  }
  cout << "NO\n";
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
