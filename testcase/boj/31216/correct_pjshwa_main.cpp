#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXV = 1e6;
vector<int> pr, spr;
ll lp[MAXV + 1];

void solve() {
  int n; cin >> n;
  cout << spr[n - 1] << '\n';
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

  for (int i = 2; i <= pr.size(); ++i) {
    if (lp[i] == i) spr.push_back(pr[i - 1]);
  }

  int t = 1;
  cin >> t;
  while (t--) solve();
}
