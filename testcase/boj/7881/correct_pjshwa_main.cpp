#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const ll MAX = 4e6;
ll lp[MAX + 1], d[MAX + 1];
vector<int> pr;

void solve() {
  int n;
  cin >> n;
  cout << d[n] << '\n';
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

  d[1] = 0;
  for (int i = 2; i <= 1e6; i++) {
    int l = 3 * i + 7;
    d[i] = d[i - 1] + (lp[l] == l);
  }

  int t = 1;
  cin >> t;
  while (t--) solve();
}
