#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 3e6;
int lp[MAX + 1];
vector<int> pr;
int d[MAX + 1];

void solve() {
  int N; cin >> N;
  cout << d[N] << '\n';
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

  for (int p : pr) {
    for (int o : pr) {
      if (o >= p - 1) break;
      if (o >= 500) break;

      int r = p - o - 1;
      if (lp[r] != r) continue;

      d[p] = max(d[p], d[o] + d[r]);
    }
    d[p]++;
  }

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
