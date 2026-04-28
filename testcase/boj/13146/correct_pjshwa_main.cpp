#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e6, INF = 0x3f3f3f3f;

void solve() {
  int N; cin >> N;

  stack<int> S; ll ans = 0;
  for (int i = 0; i < N; i++) {
    int x; cin >> x;
    if (!S.empty() && S.top() <= x) {
      ans += x - S.top();
      while (!S.empty() && S.top() <= x) S.pop();
    }
    S.push(x);
  }

  int maxx = 0, minx = INF;
  while (!S.empty()) {
    maxx = max(maxx, S.top());
    minx = min(minx, S.top());
    S.pop();
  }
  ans += maxx - minx;

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
