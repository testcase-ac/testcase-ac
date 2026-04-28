#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e6;
int lp[MAX + 1], C[MAX + 1], A[MAX + 1];
vector<int> pr;

void solve() {
  int l, r;
  cin >> l >> r;
  for (int i = l; i <= r; i++) A[i - l] = i;

  // Sieve of Eratosthenes O(n)
  for (ll i = 2; i <= MAX; ++i) {
    if (lp[i] == 0) {
      lp[i] = i;
      pr.push_back(i);
    }
    for (int j = 0; j < pr.size() && pr[j] <= lp[i] && i * pr[j] <= MAX; j++)
      lp[i * pr[j]] = pr[j];
  }

  for (int p : pr) {
    ll cp = p;
    while (cp <= r) {
      ll x = l / cp * cp;
      while (x <= r) {
        if (x >= l) {
          C[x - l]++;
          A[x - l] /= p;
        }
        x += cp;
      }
      cp *= p;
    }
  }
  for (int i = l; i <= r; i++) {
    if (A[i - l] > 1) C[i - l]++;
  }

  int ans = 0;
  for (int i = l; i <= r; i++) {
    int t = C[i - l];
    // cout << "i = " << i << ", t = " << t << '\n';
    if (t >= 2 && lp[t] == t) ans++;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
