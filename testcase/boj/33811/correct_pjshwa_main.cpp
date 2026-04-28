#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; string S; cin >> N >> S;
  int mind = 0, ans = 0, g = 0, s = 0;
  for (int i = 0; i < N; ++i) {
    string sub = S.substr(i, 4);
    if (sub == "GSHS") ++g;
    if (sub == "SSHS") ++s;
    mind = min(mind, s - g);
    ans = max(ans, s - g - mind);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
