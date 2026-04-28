#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N;

  map<int, int> tal;
  for (int i = 0; i < 3 * N; ++i) {
    int x; cin >> x; ++tal[x];
  }

  for (auto& [_, v] : tal) {
    if (v % 3) return cout << "Y\n", void();
  }
  cout << "N\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
