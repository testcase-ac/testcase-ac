#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int A, B; cin >> A >> B;
  vector<ll> V(A + B + 1);
  for (int i = 0; i < A + B + 1; i++) cin >> V[i];

  ll u = V[0];
  for (int i = 0; i < A; i++) u &= V[i + 1];
  for (int i = 0; i < B; i++) u |= V[A + i + 1];
  cout << u << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
