#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; string S; cin >> N >> S;

  int ans = 1, sta = 0;
  for (int i = 1; i < N; ++i) {
    ++sta;

    bool f = true;
    for (int j = sta; j < N; ++j) f &= S[j] == S[j - sta];
    if (f) ++ans, sta = 0;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
