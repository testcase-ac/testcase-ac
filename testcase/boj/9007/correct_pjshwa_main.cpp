#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int INF = 1e9 + 7;

void solve() {
  int n, k;
  cin >> k >> n;

  vector<int> a, b, t;
  for (int i = 0, x; i < n; i++) {
    cin >> x;
    t.push_back(x);
  }
  for (int i = 0, x; i < n; i++) {
    cin >> x;
    for (int e : t) a.push_back(x + e);
  }

  t.clear();
  for (int i = 0, x; i < n; i++) {
    cin >> x;
    t.push_back(x);
  }
  for (int i = 0, x; i < n; i++) {
    cin >> x;
    for (int e : t) b.push_back(x + e);
  }

  sort(b.begin(), b.end());
  
  int ans, cdiff = INF;
  for (int e : a) {
    auto it = lower_bound(b.begin(), b.end(), k - e);

    if (it != b.begin()) {
      int val = *(it - 1), diff = abs(k - (e + val));
      if (diff < cdiff) {
        cdiff = diff;
        ans = e + val;
      }
      else if (diff == cdiff) {
        ans = min(ans, e + val);
      }
    }
    if (it != b.end()) {
      int val = *it, diff = abs(k - (e + val));
      if (diff < cdiff) {
        cdiff = diff;
        ans = e + val;
      }
      else if (diff == cdiff) {
        ans = min(ans, e + val);
      }
    }
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
