#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e4;
vector<int> pr;
int lp[MAX + 1];

void solve() {
  int N; cin >> N;

  map<int, int> d; int ans = 0;
  for (int i = 0; i < N; ++i) {
    int x; cin >> x;
    ++d[x];

    for (int p : pr) {
      if (x % p) continue;
      d[x] = max(d[x], d[p] + 1);
      d[x] = max(d[x], d[x / p] + 1);
    }
    ans = max(ans, d[x]);
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
