#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 100, INF = 0x3f3f3f3f;
int d[MAX + 1][8];

void solve() {
  int N; string S, T;
  cin >> N >> S >> T;

  for (int i = 0; i <= N; i++) fill(d[i], d[i] + 8, -INF);
  d[0][0] = 0, d[0][4] = 1;

  for (int i = 1; i <= N; i++) {
    int c = S[i - 1] - '0';
    for (int ps = 0; ps < 8; ps++) for (int o = 0; o < 2; o++) {
      if (o == 0 && i < N && T[i] == '*') continue;

      int ns = ps >> 1;
      if (o) ns += 4;
      if (__builtin_popcount(ns) == c) {
        d[i][ns] = max(d[i][ns], d[i - 1][ps] + o);
      }
    }
  }

  int ans = 0;
  for (int j = 0; j < 4; j++) ans = max(ans, d[N][j]);
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
