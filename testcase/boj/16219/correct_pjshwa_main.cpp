#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 2e5;
int A[MAXN], N, inv;

void u(int i, int x) {
  if (i < 0 || i >= N - 1) return;
  inv += x * (A[i] > A[i + 1]);
}

void t(int i, int j) {
  if (i == j) return;
  if (i > j) swap(i, j);
  if (i + 1 == j) {
    u(i - 1, -1); u(i, -1); u(j, -1);
    swap(A[i], A[j]);
    u(i - 1, 1); u(i, 1); u(j, 1);
    return;
  }
  u(i - 1, -1); u(i, -1);
  u(j - 1, -1); u(j, -1);
  swap(A[i], A[j]);
  u(i - 1, 1); u(i, 1);
  u(j - 1, 1); u(j, 1);
}

void solve() {
  cin >> N;
  for (int i = 0; i < N; ++i) cin >> A[i];
  for (int i = 0; i < N - 1; ++i) u(i, 1);

  int M; cin >> M;
  while (M--) {
    int i, j; cin >> i >> j;
    t(i, j);
    if (N > 2 && inv > 0) cout << "-1 ";
    else cout << inv << ' ';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
