#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, M, K; cin >> N >> M >> K;

  int acc = 0;
  for (int i = 1; i <= M; i++) {
    int t, r; cin >> t >> r;
    acc += r;
    if (acc > K) return cout << i << ' ' << "1\n", void();
  }
  cout << "-1\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
