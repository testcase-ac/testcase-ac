#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int n; cin >> n;

  vector<int> a(n), ans;
  for (int i = 0; i < n; i++) cin >> a[i];
  sort(a.begin(), a.end());

  int l = 0, r = n - 1;
  while (l < r) {
    ans.push_back(a[l++]);
    ans.push_back(a[r--]);
  }
  if (l == r) ans.push_back(a[l]);

  reverse(ans.begin(), ans.end());
  for (int i = 0; i < n; i++) cout << ans[i] << " \n"[i == n - 1];
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
