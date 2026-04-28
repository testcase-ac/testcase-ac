#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MOD = 998244353;

void solve() {
  int N; cin >> N;

  vector<pii> xr, yr;
  for (int i = 0; i < N; i++) {
    int x1i, y1i, x2i, y2i; cin >> x1i >> y1i >> x2i >> y2i;
    xr.emplace_back(x1i, x2i);
    yr.emplace_back(y1i, y2i);
  }
  sort(xr.begin(), xr.end());
  sort(yr.begin(), yr.end());

  ll ans = 0, pcnt = 0, psum = 0;
  priority_queue<int, vector<int>, greater<int>> U;

  for (auto& [s, e] : xr) {
    while (!U.empty() && U.top() < s) {
      ++pcnt;
      psum = (psum + U.top()) % MOD;
      U.pop();
    }

    ll add = (pcnt * s + MOD - psum) % MOD;
    ans = (ans + add) % MOD;
    U.push(e);
  }

  pcnt = 0, psum = 0;
  while (!U.empty()) U.pop();

  for (auto& [s, e] : yr) {
    while (!U.empty() && U.top() < s) {
      ++pcnt;
      psum = (psum + U.top()) % MOD;
      U.pop();
    }

    ll add = (pcnt * s + MOD - psum) % MOD;
    ans = (ans + add) % MOD;
    U.push(e);
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
