#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 200;
int V[MAXN][MAXN], C[MAXN][MAXN];

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) cin >> C[i][j];

  for (int k = 0; k < N; ++k) for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) {
    if (i == j || i == k || j == k) continue;
    if (C[i][j] == C[i][k] + C[k][j]) V[i][j] = 1;
  }

  for (int i = 0; i < N; ++i) for (int j = i + 1; j < N; ++j) {
    if (!V[i][j]) cout << i + 1 << ' ' << j + 1 << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
