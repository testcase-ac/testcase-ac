#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 3000;
int A[MAX + 1][MAX + 1], p[MAX + 1], inv[MAX + 1];

void solve() {
  int N, M, q;
  cin >> N >> M >> q;
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < M; ++j) {
      cin >> A[i][j];
    }
    p[i] = i;
  }

  while (q--) {
    int op;
    cin >> op;
    if (op == 0) {
      int i, j, k;
      cin >> i >> j >> k;
      A[p[i]][j] = k;
    }
    if (op == 1) {
      int i, j;
      cin >> i >> j;
      swap(p[i], p[j]);
    }
  }

  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < M; ++j) {
      cout << A[p[i]][j] << ' ';
    }
    cout << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
