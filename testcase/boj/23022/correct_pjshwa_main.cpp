#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5, INF = 0x3f3f3f3f;
pii v[MAX];

void solve() {
  int n, S;
  cin >> n >> S;
  for (int i = 0; i < n; i++) cin >> v[i].first;
  for (int i = 0; i < n; i++) cin >> v[i].second;
  sort(v, v + n);

  priority_queue<pii> pq;
  int last = S, li;
  for (li = 0; li < n; li++) {
    auto [ti, vi] = v[li];
    if (ti < S) pq.push({vi, ti});
    else break;
  }

  ll ans = 0;
  for (int i = li; i < n; i++) {
    auto [ti, vi] = v[i];

    int diff = ti - last;
    for (int j = last; j < last + diff; j++) {
      if (pq.empty()) break;
      auto [v, t] = pq.top();
      pq.pop();
      ans += (ll)(j - t) * v;
    }

    last = ti;
    pq.push({vi, ti});
  }

  for (int j = last;; j++) {
    if (pq.empty()) break;
    auto [v, t] = pq.top();
    pq.pop();
    ans += (ll)(j - t) * v;
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
