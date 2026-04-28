#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 100;
const int dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};
int A[MAX + 1][MAX + 1], vis[MAX + 1][MAX + 1];

void solve() {
  int N, M, L, E, K;
  cin >> N >> M >> L >> E >> K;

  int si, sj;
  for (int i = 1; i <= N; ++i) for (int j = 1; j <= M; ++j) {
    cin >> A[i][j];
    if (A[i][j] == -3) si = i, sj = j;
  }

  priority_queue<tii, vector<tii>, greater<tii>> pq;
  pq.push({0, si, sj});
  vis[si][sj] = 1;

  bool g = false;
  while (!pq.empty()) {
    auto [d, i, j] = pq.top(); pq.pop();
    if (d >= L) break;

    E += d;
    while (E >= L) {
      E -= L; L++;
    }

    if (A[i][j] == -2) g = true;
    for (int k = 0; k < 4; ++k) {
      int ni = i + dx[k], nj = j + dy[k];
      if (ni < 1 || ni > N || nj < 1 || nj > M) continue;
      if (A[ni][nj] == -1) continue;
      if (vis[ni][nj]) continue;

      int x = A[ni][nj] < 0 ? 0 : A[ni][nj];
      pq.push({x, ni, nj});
      vis[ni][nj] = 1;
    }
  }

  if (g && L >= K) cout << "O\n";
  else cout << "X\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
