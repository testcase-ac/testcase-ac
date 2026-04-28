#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 10000;
int lp[MAX + 1];
vector<int> pr;

void solve() {
  int n;
  cin >> n;

  int sz = pr.size();
  for (int i = 0; i < sz - 1; i++) {
    if (pr[i] * pr[i + 1] > n) {
      cout << pr[i] * pr[i + 1] << '\n';
      return;
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
