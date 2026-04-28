#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 20;
double A[MAX][MAX];
double d[1 << MAX];

void solve() {
  int N;
  cin >> N;
  for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) {
    cin >> A[i][j];
    A[i][j] /= 100;
  }

  d[0] = 1;
  for (int s = 0; s < (1 << N); s++) {
    int u = __builtin_popcount(s) - 1;
    for (int j = 0; j < N; j++) {
      if (!(s & (1 << j))) continue;
      d[s] = max(d[s], d[s ^ (1 << j)] * A[u][j]);
    }
  }

  cout << fixed << setprecision(10) << d[(1 << N) - 1] * 100 << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
