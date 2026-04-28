#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int INF = 0x3f3f3f3f;

void solve() {
  int N; cin >> N;

  int amax = 0, amin = INF;
  priority_queue<int, vector<int>, greater<int>> pq;
  for (int i = 0; i < N; ++i) {
    int x; cin >> x;
    amax = max(amax, x); amin = min(amin, x);
    pq.push(x);
  }

  int cmax = amax, ans = amax - amin;
  while (pq.top() < amax) {
    int x = pq.top(); pq.pop();
    ans = min(ans, cmax - x);
    cmax = max(cmax, x * 2);
    pq.push(x * 2);
  }
  ans = min(ans, cmax - amax);
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
