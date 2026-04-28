#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  ll n, q; cin >> n;

  vector<int> P(2 * n - 1, -1);
  for (int i = 0; i <= 2 * n; i += 2) P[i] = i / 2 + 1;

  int it = n - 1;
  while (it--) {
    int i = n + it;
    while (P[i] != -1) --i;
    swap(P[i], P[n + it]);
  }

  cout << "P = ";
  for (int i = 0; i < n; i += 1) cout << P[i] << " ";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
