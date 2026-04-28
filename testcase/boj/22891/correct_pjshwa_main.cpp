#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 500;
int lp[MAX + 1];
vector<int> pr;

map<int, ll> factorize(ll n) {
  map<int, ll> res;
  for (int prime : pr) {
    while (n % prime == 0) res[prime]++, n /= prime;
  }
  if (n > 1) res[0] = 1;
  return res;
}

int main() {
  fast_io();

  int t, n;
  cin >> t;

  // Sieve of Eratosthenes O(n)
  for (ll i = 2; i <= 500; ++i) {
    if (lp[i] == 0) {
      lp[i] = i;
      pr.push_back(i);
    }
    for (int j = 0; j < pr.size() && pr[j] <= lp[i] && i * pr[j] <= MAX; j++)
      lp[i * pr[j]] = pr[j];
  }

  for (int tc = 1; tc <= t; tc++) {
    cin >> n;
    ll sum = 0;
    map<int, ll> pcnt;
    for (int i = 0; i < n; i++) {
      ll ni, pi;
      cin >> ni >> pi;
      pcnt[ni] = pi;
      sum += ni * pi;
    }

    ll ans = 0;
    for (int d = 1; d <= min(30000LL, sum - 1); d++) {
      auto fb = factorize(sum - d);
      if (fb[0] == 1) continue;

      bool able = true;
      ll fasum = 0;
      for (int p : pr) {
        ll c = pcnt[p];
        if (fb[p] > c) able = false;
        else fasum += (c - fb[p]) * p;
      }
      if (able && fasum + d == sum) ans = max(ans, sum - d);
    }

    cout << "Case #" << tc << ": " << ans << '\n';
  }
}
