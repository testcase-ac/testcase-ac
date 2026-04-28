#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const ll INF = 9e18;
vector<int> S;
set<int> vis;

ll C(int n, int k) {
  if (n < 0 || k < 0 || n < k) return 0;
  ll ans = 1;
  for (int i = 1; i <= k; i++) {
    ans *= (n - i + 1);
    ans /= i;
  }
  return ans;
}

void solve() {
  int n;
  cin >> n;
  S.push_back(0);
  for (int i = 1, x; i <= n; i++) {
    cin >> x;
    S.push_back(x);
  }
  sort(S.begin(), S.end());

  priority_queue<pll, vector<pll>, greater<pll>> pq;
  for (int i = 0; i < n + 1; i++) {
    vis.insert(S[i]);
    pq.push({0, S[i]});
  }

  int q;
  cin >> q;
  while (q) {
    int c = pq.top().second;
    pq.pop();

    if (c) q--, cout << c << ' ';

    for (int w : {c - 1, c + 1}) {
      if (w <= 0 || vis.count(w)) continue;
      vis.insert(w);

      auto it = upper_bound(S.begin(), S.end(), w);
      if (it == S.end()) pq.push({INF, w});
      else {
        int l = *(it - 1), r = *it;
        ll inc = C(r - l - 1, 2) - C(w - l - 1, 2) - C(r - w - 1, 2);
        pq.push({inc, w});
      }
    }
  }
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
