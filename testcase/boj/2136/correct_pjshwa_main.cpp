#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int n, l;
  cin >> n >> l;

  int left = 0, lmax = 0, rmax = 0;
  vector<pii> a(n);
  for (int i = 0, x; i < n; i++) {
    cin >> x;
    if (x < 0) {
      left++;
      lmax = max(lmax, -x);
    }
    else rmax = max(rmax, l - x);
    a[i] = {abs(x), i + 1};
  }
  sort(a.begin(), a.end());

  if (lmax < rmax) cout << a[left].second << ' ' << rmax << '\n';
  else cout << a[left - 1].second << ' ' << lmax << '\n';
}

int main() {
  fast_io();
  
  int t = 1;
  // cin >> t;
  while (t--) solve();
}
