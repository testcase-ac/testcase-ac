#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 250;
ll lp[MAX + 1], d[MAX + 1];
vector<int> pr;

void solve() {
  int P;
  cin >> P;
  cout << d[P] << '\n';
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

  d[2] = 1;
  for (int i = 0; i < pr.size(); i++) {
    int p = pr[i];
    for (int v = p - 14; v < p; v++) {
      if (v < 2 || lp[v] != v) continue;
      d[p] += d[v];
    }
  }

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
