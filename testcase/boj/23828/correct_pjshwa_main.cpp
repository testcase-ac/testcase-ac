#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5, MOD = 1e9 + 7;
int t[MAX + 1];

void solve() {
  int n, m;
  cin >> n >> m;
  for (int i = 0; i < n; i++) {
    int x;
    cin >> x;
    t[x]++;
  }

  vector<ll> coefs;
  for (int i = 1; i <= MAX; i++) {
    if (t[i]) coefs.push_back(((ll)t[i] * i) % MOD);
  }

  vector<ll> ans = {1};
  int sz = 1;
  for (auto coef : coefs) {
    ans.push_back(0);
    sz++;

    for (int i = sz - 1; i >= 1; i--) {
      ans[i] = (ans[i] + coef * ans[i - 1]) % MOD;
    }
  }

  cout << ans[m] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
