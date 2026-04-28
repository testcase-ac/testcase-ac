#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void compress(vector<int>& a) {
  sort(a.begin(), a.end());
  a.erase(unique(a.begin(), a.end()), a.end());
}

void solve() {
  int L, N; cin >> L >> N;

  vector<int> OU, OD, EU, ED;
  for (int i = 0; i < N; i++) {
    int x, y; cin >> x >> y;

    int a = x + y, b = x - y;
    if (a & 1) OU.push_back(a), OD.push_back(b);
    else EU.push_back(a), ED.push_back(b);
  }

  compress(OU); compress(OD); compress(EU); compress(ED);
  ll ans = 0;
  for (int e : OU) ans += L - abs(e - L + 1);
  for (int e : EU) ans += L - abs(e - L + 1);
  for (int e : OD) ans += L - abs(e);
  for (int e : ED) ans += L - abs(e);

  for (int a : OU) {
    int l = max(-a, a - 2 * L + 1);
    int u = min(a, 2 * L - a - 1);
    if (l > u) continue;

    auto ut = upper_bound(OD.begin(), OD.end(), u);
    auto lt = lower_bound(OD.begin(), OD.end(), l);
    ans -= ut - lt;
  }
  for (int a : EU) {
    int l = max(-a, a - 2 * L + 1);
    int u = min(a, 2 * L - a - 1);
    if (l > u) continue;

    auto ut = upper_bound(ED.begin(), ED.end(), u);
    auto lt = lower_bound(ED.begin(), ED.end(), l);
    ans -= ut - lt;
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
