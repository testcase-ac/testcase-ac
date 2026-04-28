#include <bits/stdc++.h>
#define ll long long
using namespace std;

const ll MAX = 1e4;
ll lp[MAX + 1];
int main() {
  vector<int> pr;

  // Sieve of Eratosthenes O(n)
  for (ll i = 2; i <= MAX; ++i) {
    if (lp[i] == 0) {
      lp[i] = i;
      pr.push_back(i);
    }
    for (int j = 0; j < pr.size() && pr[j] <= lp[i] && i * pr[j] <= MAX; j++)
      lp[i * pr[j]] = pr[j];
  }

  int n, k, m = 1e9;
  cin >> n >> k;

  n = n + k - 1;
  k--;

  ll ans = 1, p, c;
  for (int prime : pr) {
    c = prime;
    p = 0;
    while (c <= n) {
      p += (n / c) - (k / c) - ((n - k) / c);
      c *= prime;
    }

    while (p--) ans = (ans * prime) % m;
  }

  cout << ans << '\n';
}
