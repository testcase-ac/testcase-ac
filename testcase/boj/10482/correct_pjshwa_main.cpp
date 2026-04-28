#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using matrix = vector<vector<ll>>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const ll MAX = 32000;
ll lp[MAX + 1];

void solve() {
  int N;
  cin >> N;
  cout << N << " has ";

  vector<int> ans;
  for (int i = 2; i <= N / 2; i++) {
    int j = N - i;
    if (lp[i] == i && lp[j] == j) ans.push_back(i);
  }

  cout << ans.size() << " representation(s)\n";
  for (int e : ans) cout << e << '+' << N - e << '\n';
}

int main() {
  fast_io();

  vector<int> pr;

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
