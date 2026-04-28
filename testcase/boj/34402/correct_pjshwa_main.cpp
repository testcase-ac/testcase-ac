#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  ll N, K; cin >> N >> K;

  N %= (2 * K + 2);
  if (N == 0) N = 2 * K + 2;

  if (N == 1) cout << "(2,3) (2,4) (3,4)\n";
  else if (N == 2) cout << "(1,3) (1,4) (3,4)\n";
  else if (N <= K + 1) cout << "(1,2) (1,3) (1,4)\n";
  else if (N == K + 2) cout << "(1,2) (1,4) (2,4)\n";
  else cout << "(1,2) (1,3) (2,3)\n";
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
