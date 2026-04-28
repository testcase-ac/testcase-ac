#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int INF = 1e9 + 7;

void solve() {
  int n;
  cin >> n;

  vector<int> v1, v2;
  deque<int> d1, d2;

  if (n == 1) {
    v1.push_back(1);
    d1.push_back(1);
    v2.push_back(2);
    d2.push_back(2);
  }
  else {
    for (int i = 0; i < n - 1; i++) {
      v1.push_back(2 * n - 3 - i);
      d1.push_back(2 * n - 3 - i);
    }
    v1.push_back(2 * n - 2);
    d1.push_back(2 * n - 2);

    v2.push_back(2 * n - 1);
    d2.push_back(2 * n - 1);
    for (int i = 0; i < n - 2; i++) {
      v2.push_back(n - 2 - i);
      d2.push_back(n - 2 - i);
    }
    v2.push_back(2 * n);
    d2.push_back(2 * n);
  }

  int r = 0, it = 0;
  ll ans = 0;
  while (!d1.empty() || !d2.empty()) {
    int d1v = d1.empty() ? INF : min(d1.front(), d1.back());
    int d2v = d2.empty() ? INF : min(d2.front(), d2.back());
    int dv = min(d1v, d2v);

    if (!d1.empty() && dv == d1.front()) d1.pop_front();
    if (!d1.empty() && dv == d1.back()) d1.pop_back();
    if (!d2.empty() && dv == d2.front()) d2.pop_front();
    if (!d2.empty() && dv == d2.back()) d2.pop_back();

    ans += (ll)dv * r;
    r += ++it;
  }

  cout << ans << '\n';
  for (int e : v1) cout << e << ' ';
  cout << '\n';
  for (int e : v2) cout << e << ' ';
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
