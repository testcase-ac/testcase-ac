#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, M; cin >> N >> M;

  int c;
  for (c = N; c >= 1; --c) {
    int maxv = (N - c) * c + c - 1;
    if (maxv >= M && M >= c - 1) break;
  }

  if (c == 0) {
    for (int i = 0; i < N; ++i) cout << "0 ";
  }
  else {
    cout << "0 ";
    for (int i = 0; i < c - 1; ++i) cout << "1 ";

    M -= c - 1;
    for (int i = 0; i < N - c; ++i) {
      int v = min(M, c);
      cout << v << " ";
      M -= v;
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
