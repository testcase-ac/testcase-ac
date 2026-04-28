#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; string S; cin >> N >> S;

  vector<int> str_v; int streak = 0;
  for (int i = 0; i < N; ++i) {
    if (S[i] == '2') ++streak;
    else {
      if (streak) str_v.push_back(streak);
      streak = 0;
    }
  }
  if (streak) str_v.push_back(streak);

  ll ans = 0;
  for (ll e : str_v) {
    ans += e * (e + 1) * (e + 2) / 6;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
