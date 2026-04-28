#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const ll MAX = 5e5;
ll lp[MAX + 1];
int c[MAX + 1];

int main() {
  fast_io();

  vector<int> pr;
  c[1] = 1;

  // Sieve of Eratosthenes O(n)
  for (ll i = 2; i <= MAX; ++i) {
    if (lp[i] == 0) {
      lp[i] = i;
      c[i] = pr.size() + 2;
      pr.push_back(i);
    }
    for (int j = 0; j < pr.size() && pr[j] <= lp[i] && i * pr[j] <= MAX; j++) {
      lp[i * pr[j]] = pr[j];
      c[i * pr[j]] = c[pr[j]];
    }
  }

  int n, mx = 0;
  cin >> n;
  for (int i = 1; i <= n; i++) mx = max(mx, c[i]);
  cout << mx << '\n';
  for (int i = 1; i <= n; i++) cout << c[i] << ' ';
}
