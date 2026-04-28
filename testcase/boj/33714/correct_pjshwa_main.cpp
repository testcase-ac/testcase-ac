#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

int N, K;
map<int, int> tal;

void solve_min() {
  int last = -1;
  for (auto& [k, v] : tal) {
    if (k > last + 1) return cout << last + 1 << '\n', void();
    if (v <= K) return cout << k << '\n', void();
    last = k;
  }
  cout << last + 1 << '\n';
}

void solve_max() {
  int last = -1, K_rem = K;
  for (auto& [k, v] : tal) {
    if (k > last + 1) {
      if (K_rem >= k - last - 1) {
        K_rem -= k - last - 1;
      } else {
        return cout << last + 1 + K_rem << '\n', void();
      }
    }
    last = k;
  }
  cout << last + 1 + K_rem << '\n';
}

void solve() {
  int x; cin >> N >> K;
  for (int i = 0; i < N; ++i) cin >> x, ++tal[x];

  solve_min();
  solve_max();
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
