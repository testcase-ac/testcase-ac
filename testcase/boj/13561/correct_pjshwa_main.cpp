#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e5;
vector<ll> Wt[MAX + 1];

void solve() {
  int k, n;
  cin >> k >> n;

  vector<tuple<ll, ll, ll, ll>> a;
  for (int i = 0; i < n; i++) {
    int x, t;
    cin >> x >> t;
    x *= 2;

    a.push_back({x, t, 0, 0});
    Wt[t].push_back(x);
  }
  for (int i = 1; i <= k; i++) {
    sort(Wt[i].begin(), Wt[i].end());
    int sz = Wt[i].size();
    for (int j = 0; j < sz - 1; j++) {
      auto xi = Wt[i][j], xj = Wt[i][j + 1];
      a.push_back({(xi + xj) / 2, i, 1, xi});
    }
  }
  sort(a.begin(), a.end());

  multiset<ll> S;
  vector<bool> check(k + 1, false);
  for (auto [x, t, s, px] : a) {
    if (check[t]) continue;

    S.insert(x);
    check[t] = true;
  }

  ll mscr = 1e18, mx;
  for (auto [x, t, s, px] : a) {
    ll nscr;
    if (x & 1) {
      for (ll y : {x - 1, x + 1}) {
        nscr = max(abs(y - *S.begin()), abs(y - *S.rbegin()));
        if (nscr < mscr) {
          mscr = nscr;
          mx = y;
        }
      }
    }
  else {
      nscr = max(abs(x - *S.begin()), abs(x - *S.rbegin()));
      if (nscr < mscr) {
        mscr = nscr;
        mx = x;
      }
    }

    if (s == 1) {
      S.erase(S.find(px));
      S.insert(2 * x - px);
    }
  }

  cout << mx / 2 << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
