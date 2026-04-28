#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 300;
int a[MAX], b[MAX];

void solve() {
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> a[i];
  for (int i = 0; i < n; i++) cin >> b[i];

  map<int, int> d;
  d[0] = 0;
  d[a[0]] = b[0];
  for (int i = 1; i < n; i++) {
    map<int, int> nd;
    for (auto& [k, v] : d) nd[k] = v;
    for (auto& [k, v] : d) {
      int g = gcd(k, a[i]);
      if (nd.count(g)) nd[g] = min(nd[g], v + b[i]);
      else nd[g] = v + b[i];
    }
    d = nd;
  }

  if (d.count(1)) cout << d[1] << '\n';
  else cout << "-1\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
