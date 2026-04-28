#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 2000, MOD = 100999;
int d[MAX + 1][MAX + 1];

void solve() {
  int N; cin >> N;
  cout << d[N][N] << '\n';
}

int main() {
  fast_io();

  d[0][0] = 1;
  for (int i = 1; i <= MAX; i++) {
    for (int v = 0; v <= MAX; v++) d[i][v] = d[i - 1][v];
    for (int v = MAX; v >= i; v--) {
      d[i][v] = (d[i][v] + d[i][v - i]) % MOD;
    }
  }

  int t = 1;
  cin >> t;
  while (t--) solve();
}
