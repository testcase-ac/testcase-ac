#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MOD = 1e9 + 7;

void solve() {
  ll N; cin >> N;

  cout << (N - 1) * (N - 1) << '\n';
  for (int i = 2; i <= N; i++) cout << "1 " << i << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
