#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int C[10]{}, N; cin >> N;
  for (int i = 1; i <= N; i += 2) {
    string S = to_string(i);
    for (char c : S) ++C[c - '0'];
  }
  for (int i = 0; i < 10; ++i) cout << C[i] << " \n"[i == 9];
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
