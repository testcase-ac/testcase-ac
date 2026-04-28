#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e7;
ll lp[MAX + 1], D[MAX + 1];
vector<int> pr;

void solve() {
  int a, b, c, d;
  cin >> a >> b >> c >> d;

  memset(D, 0, sizeof(D));
  for (int f : {a - 1, d}) {
    for (int p : pr) {
      ll c = p;
      while (c <= f) {
        D[p] += f / c;
        c *= p;
      }
    }
  }

  for (int f : {b, c - 1}) {
    for (int p : pr) {
      ll c = p;
      while (c <= f) {
        D[p] -= f / c;
        c *= p;
      }
    }
  }

  for (int p : pr) {
    if (D[p] < 0) return cout << "NE\n", void();
  }
  cout << "DA\n";
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
  while (t--) solve();
}
