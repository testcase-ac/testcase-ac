#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 4e6;
ll lp[MAX + 1];
vector<int> pr;

void solve() {
  int a, b; string d;
  cin >> a >> b >> d;

  int ans = 0;
  for (int i = a; i <= b; i++) {
    if (lp[i] != i) continue;
    if (to_string(i).find(d) != string::npos) ans++;
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
