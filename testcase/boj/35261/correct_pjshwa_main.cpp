#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, ans = 5; string S, T = "eagle"; cin >> N >> S;
  for (int i = 0; i <= N - 5; ++i) {
    int cur = 0;
    for (int j = 0; j < 5; ++j) cur += (S[i + j] != T[j]);
    ans = min(ans, cur);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
