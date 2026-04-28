#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

vector<int> pr;
const ll MAX = 1e6;
ll lp[MAX + 1];

void solve() {
  int n;
  cin >> n;

  for (int it = 0;; it++) {
    if (n == 0 || n == 2) return cout << it << '\n', void();
    for (int p : pr) {
      if (lp[n - p] == n - p) {
        n = n - 2 * p;
        break;
      }
    }
  }
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
