#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2.5e5;
int a[MAX];

void solve() {
  int n, q;
  cin >> n >> q;

  vector<int> v;
  for (int i = 0; i < n; i++) cin >> a[i], v.push_back(a[i]);
  sort(v.begin(), v.end());

  while (q--) {
    int x, y;
    cin >> x >> y;

    int xc = max(0L, n + 1 - y - (lower_bound(v.begin(), v.end(), x) - v.begin()));
    int yc = max(0, a[y - 1] - (x - 1));

    if (yc == 0) cout << "0\n";
    else cout << xc + yc - 1 << "\n";
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
