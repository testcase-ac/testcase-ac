#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e7;
int lp[MAX + 1];
vector<int> pr;

void solve() {
  ll a, b;
  cin >> a >> b;

  int ans = 0;
  for (int p : pr) {
    __int128_t cur = (ll)p * p;
    while (cur <= b) {
      if (a <= cur) ans++;
      cur *= p;
    }
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  // Sieve of Eratosthenes O(n)
  for (ll i = 2; i <= MAX; ++i) {
    if (lp[i] == 0) {
      lp[i] = i;
      pr.push_back(i);
    }
    for (int j = 0; j < pr.size() && pr[j] <= lp[i] && i * pr[j] <= MAX; j++)
      lp[i * pr[j]] = pr[j];
  }

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
