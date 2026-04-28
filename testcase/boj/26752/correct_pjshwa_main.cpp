#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int C[3]; cin >> C[0] >> C[1] >> C[2];

  ++C[2];
  if (C[2] == 60) C[2] = 0, ++C[1];
  if (C[1] == 60) C[1] = 0, ++C[0];
  if (C[0] == 24) C[0] = 0;

  cout << setfill('0') << setw(2) << C[0] << ':'
       << setfill('0') << setw(2) << C[1] << ':'
       << setfill('0') << setw(2) << C[2] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
