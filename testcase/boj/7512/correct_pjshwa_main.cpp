#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const ll MAX = 1e7;
ll lp[MAX + 1];
bool cs[MAX + 1], ns[MAX + 1];
vector<int> pr;

int tc;
void solve() {
  cout << "Scenario " << ++tc << ":\n";

  memset(cs, 0, sizeof(cs));
  for (int p : pr) cs[p] = true;

  int n;
  cin >> n;

  for (int i = 1, x; i <= n; i++) {
    cin >> x;

    ll s = 0;
    for (int j = 0; j < x; j++) s += pr[j];

    if (cs[s]) ns[s] = true;
    for (int j = x; j < pr.size(); j++) {
      s += (pr[j] - pr[j - x]);
      if (s > MAX) break;
      if (cs[s]) ns[s] = true;
    }

    for (int p : pr) cs[p] &= ns[p];
    memset(ns, 0, sizeof(ns));
  }

  for (int p : pr) if (cs[p]) {
    cout << p << '\n';
    break;
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
  cin >> t;
  while (t--) {
    solve();
    if (t) cout << '\n';
  }
}
