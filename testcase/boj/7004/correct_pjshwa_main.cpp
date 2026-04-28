#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int N;
void solve() {
  ll S;
  priority_queue<
    tuple<ll, int, int>,
    vector<tuple<ll, int, int>>,
    greater<tuple<ll, int, int>>
  > pq;

  for (int i = 0, k; i < N; i++) {
    cin >> k;
    pq.push({1, 1, k - 2});
  }
  cin >> S;

  int it = 5;
  map<ll, set<int>> inv;
  ll mval;
  while (1) {
    auto [c, x, k] = pq.top(); pq.pop();

    if (c >= S) {
      inv[c].insert(k + 2);
      if (inv[c].size() == 2) it--;
    }

    x++;
    ll nterm = k * x * (x + 1) / 2 - (k - 1) * x;
    pq.push({nterm, x, k});

    if (it == 0) {
      mval = c;
      break;
    }
  }

  while (1) {
    auto [c, x, k] = pq.top(); pq.pop();
    if (c > mval) break;

    inv[c].insert(k + 2);

    x++;
    ll nterm = k * x * (x + 1) / 2 - (k - 1) * x;
    pq.push({nterm, x, k});
  }

  for (auto& [k, vv] : inv) {
    if (vv.size() == 1) continue;
    
    cout << k << ':';
    for (int e : vv) cout << e << ' ';
    cout << '\n';
  }
}

int main() {
  fast_io();

  int it = 0;
  while (cin >> N) {
    if (N == 0) break;
    if (it++) cout << '\n';
    solve();
  }
}
