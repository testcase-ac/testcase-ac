#include <bits/stdc++.h> 
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const ll MAX = 1000, INF = 1e18;
ll A[MAX][MAX], d[MAX][MAX];

void solve() {
  int N, M; cin >> N >> M;
  for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) cin >> A[i][j];

  for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) {
    ll v = i == 0 && j == 0 ? 0 : INF;
    if (i) v = min(v, d[i - 1][j]);
    if (j) v = min(v, d[i][j - 1]);
    d[i][j] = v + A[i][j];
  }

  int H; cin >> H;
  if (d[N - 1][M - 1] <= H) cout << "YES\n" << d[N - 1][M - 1] << '\n';
  else cout << "NO\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
