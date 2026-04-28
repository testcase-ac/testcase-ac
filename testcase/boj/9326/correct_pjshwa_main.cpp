#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

ll lpow(ll x, ll y, ll m) {
  ll r = 1;
  x %= m;
  while (y) {
    if (y & 1) r = (r * x) % m;
    x = (x * x) % m;
    y >>= 1;
  }
  return r;
}

void solve() {
  int n;
  cin >> n;

  vector<int> ans;
  for (int i = 2; i * i <= n; i++) {
    int cnt = 0;
    while (n % i == 0) {
      n /= i;
      cnt++;
    }

    int pw = 1;
    while (cnt) {
      if (cnt & 1) ans.push_back(lpow(i, pw, 1e18));

      pw *= 2;
      cnt >>= 1;
    }
  }
  if (n > 1) ans.push_back(n);

  sort(ans.begin(), ans.end());
  for (int x : ans) cout << x << ' ';
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
