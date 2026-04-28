#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e5, MAXV = 1e6;
int lp[MAXV + 1], X[MAXV + 1];
vector<int> pr;

void solve() {
  for (int i = 2; i <= MAXV; ++i) {
    X[i] = X[i - 1];
    if (lp[i] == i) ++X[i];
  }

  int Q; cin >> Q;
  while (Q--) {
    int l, r; cin >> l >> r;
    int cnt = X[r] - X[l - 1];
    if (cnt & 1) cout << pr[(X[r] + X[l - 1]) / 2] << '\n';
    else cout << "-1\n";
  }
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

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
