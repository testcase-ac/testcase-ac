#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5 + 5000;
int lp[MAX + 1];
vector<int> pr;
int pn;
int a[200];

void solve() {
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> a[i];
  sort(a, a + n);

  int ans = 1e9;
  for (int j = 0; j + n < pn; j++) {
    int cur = 0;
    for (int i = 0; i < n; i++) cur += abs(a[i] - pr[j + i]);
    ans = min(ans, cur);
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

  pn = pr.size();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
