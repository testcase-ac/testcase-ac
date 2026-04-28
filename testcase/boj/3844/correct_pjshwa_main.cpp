#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e7, MOD = 1e9 + 7;
int lp[MAX + 1];
vector<int> pr;
int n;

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
  ll ans = 1;
  for (int p : pr) {
    if (p > n) break;

    int cnt = 0;
    ll c = p;
    while (c <= n) {
      cnt += (n / c);
      c *= p;
    }

    if (cnt & 1) cnt--;
    ans = (ans * lpow(p, cnt, MOD)) % MOD;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  for (int i = 2; i <= MAX; ++i) {
    if (lp[i] == 0) {
      lp[i] = i;
      pr.push_back(i);
    }
    for (int j=0; j<(int)pr.size() && pr[j]<=lp[i] && i*pr[j]<=MAX; ++j)
      lp[i * pr[j]] = pr[j];
  }

  while (1) {
    cin >> n;
    if (n == 0) break;
    solve();
  }
}
