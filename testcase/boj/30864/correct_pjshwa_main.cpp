#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N;
  for (int i = 1; i <= (N + 1) / 2; ++i) {
    cout << "[1, " << i << ", -1, 2],\n";
    cout << "[2, " << N - i + 1 << ", -1, 2],\n";
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
