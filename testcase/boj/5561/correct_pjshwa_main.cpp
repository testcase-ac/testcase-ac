#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e4, INF = 0x3f3f3f3f;
int A[MAXN + 1], d[2][MAXN + 1], nd[2][MAXN + 1];

void solve() {
  int N; cin >> N;
  for (int i = 1; i <= N - 1; i++) cin >> A[i];
  memset(d, 0x3f, sizeof(d));

  int E = N / 2;
  d[0][E] = d[1][E] = 0;
  for (int i = 1; i <= N; i++) {
    for (int v = 0; v <= N; ++v) {
      nd[0][v] = nd[1][v] = INF;
    }

    for (int v = 0; v <= N; ++v) {
      if (v > 0) nd[0][v] = min(d[0][v - 1], d[1][v - 1] + A[i - 1]);
      if (v < N) nd[1][v] = min(d[0][v + 1] + A[i - 1], d[1][v + 1]);
    }

    for (int v = 0; v <= N; ++v) {
      d[0][v] = nd[0][v];
      d[1][v] = nd[1][v];
    }
  }

  cout << min(d[0][E], d[1][E]) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
