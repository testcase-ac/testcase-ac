#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
int lp[MAX + 1];
vector<int> pr, prm;

void solve() {
  int n;
  cin >> n;
  cout << *lower_bound(prm.begin(), prm.end(), n) << '\n';
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

  for (int p1 : pr) for (int p2 : pr) {
    if (p1 == p2) continue;
    if (p1 * p2 > MAX + 10) break;
    prm.push_back(p1 * p2);
  }
  sort(prm.begin(), prm.end());

  int t = 1;
  cin >> t;
  while (t--) solve();
}
