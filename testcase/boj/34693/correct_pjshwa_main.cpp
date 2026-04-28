#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int K; cin >> K;
  int H = K / 2;
  if (K & 1) cout << H + 3 << " - " << H + 2 << " - 2\n";
  else cout << H + 5 << " - " << H + 4 << " - 3\n";
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
