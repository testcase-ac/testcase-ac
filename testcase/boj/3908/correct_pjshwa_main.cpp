#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const ll MAX = 1120;
ll lp[MAX + 1], d[MAX + 1][15];
vector<int> pr;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  // Sieve of Eratosthenes O(n)
  for (ll i = 2; i <= MAX; ++i) {
    if (lp[i] == 0) {
      lp[i] = i;
      pr.push_back(i);
    }
    for (int j = 0; j < pr.size() && pr[j] <= lp[i] && i * pr[j] <= MAX; j++) lp[i * pr[j]] = pr[j];
  }

  d[0][0] = 1;
  for (int p : pr) {
    for (int i = MAX; i >= p; i--) for (int j = 1; j <= 14; j++) d[i][j] += d[i - p][j - 1];
  }

  int t, n, k;
  cin >> t;
  while (t--) {
    cin >> n >> k;
    cout << d[n][k] << '\n';
  }
}
