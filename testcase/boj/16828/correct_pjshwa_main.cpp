#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e4, MAXV = 1e4;
ll d[2][MAXV + 1];

void solve() {
  int C, N, M;
  cin >> C >> N >> M;

  for (int i = 1; i <= N; i++) {
    int si, pi;
    cin >> si >> pi;

    int x = i & 1;
    for (int v = 0; v <= MAXV; v++) d[x][v] = d[1 - x][v];
    for (int v = 0; v <= MAXV; v++) {
      if (v + si > MAXV) break;
      d[x][v + si] = max(d[x][v + si], d[1 - x][v] + pi);
    }
  }

  for (int v = 1; v <= MAXV; v++) d[N & 1][v] = max(d[N & 1][v], d[N & 1][v - 1]);
  for (int i = 1; i <= M; i++) {
    cout << d[N & 1][C / i] * i << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
