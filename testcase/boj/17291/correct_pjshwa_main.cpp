#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 20;
int d[MAX + 1];

void solve() {
  int N; cin >> N;

  d[1] = 1; d[2] = 2; d[3] = 4; d[4] = 7;
  for (int i = 5; i <= N; i++) {
    d[i] = d[i - 1] * 2;
    if (i % 2 == 0) d[i] -= (d[i - 4] + d[i - 5]);
  }
  cout << d[N] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
