#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2e5;
priority_queue<ll, vector<ll>, greater<ll>> q[3];
set<ll> values;
int cv[3];

void solve() {
  int n;
  ll l;
  cin >> n >> l;

  ll ans = 0;
  for (int i = 0; i < n; i++) {
    string cs;
    ll c, x, dir;
    cin >> cs >> x >> dir;
    c = cs[0] - 'A';

    if (dir) {
      ans += l - x;
      cv[c]++;
    }
    else {
      q[c].push(x);
      values.insert(x);
    }
  }

  for (ll v : values) {
    vector<int> is;
    for (int i = 0; i < 3; i++) {
      if (!q[i].empty() && q[i].top() == v) {
        q[i].pop();
        is.push_back(i);
        ans += l + v;
      }
    }

    if (is.size() >= 2) {
      for (int i : is) cv[i]++;
    }
    else cv[(is[0] + 1) % 3]++;
  }

  cout << ans << '\n';
  for (int i = 0; i < 3; i++) cout << cv[i] << ' ';
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
