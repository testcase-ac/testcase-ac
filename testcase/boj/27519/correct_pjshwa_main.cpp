#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXV = 1e5, MOD = 1e9 + 7;

vector<int> pr;
int lp[MAXV + 1], d[MAXV + 1];

void solve() {
  int N; cin >> N;
  cout << d[N] << '\n';
}

int main() {
  fast_io();

  // Sieve of Eratosthenes O(n)
  for (ll i = 2; i <= MAXV; ++i) {
    if (lp[i] == 0) {
      lp[i] = i;
      pr.push_back(i);
    }
    for (int j = 0; j < pr.size() && pr[j] <= lp[i] && i * pr[j] <= MAXV; j++)
      lp[i * pr[j]] = pr[j];
  }

  d[0] = 1;
  for (int p : pr) {
    for (int i = p; i <= MAXV; i++) d[i] = (d[i] + d[i - p]) % MOD;
  }

  int t = 1;
  cin >> t;
  while (t--) solve();
}
