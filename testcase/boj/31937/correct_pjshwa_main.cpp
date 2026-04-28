#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, M, K; cin >> N >> M >> K;

  vector<int> E(N + 1);
  while (K--) {
    int x; cin >> x;
    E[x] = 1;
  }

  vector<tuple<int, int, int>> logs;
  while (M--) {
    int t, a, b; cin >> t >> a >> b;
    logs.emplace_back(t, a, b);
  }
  sort(logs.begin(), logs.end());

  vector<int> U(N + 1);
  for (int i = 1; i <= N; ++i) {
    fill(U.begin(), U.end(), 0);
    U[i] = 1;

    for (auto& [_, s, e] : logs) {
      if (U[s]) U[e] = 1;
    }

    if (U == E) return cout << i << '\n', void();
  }

}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
