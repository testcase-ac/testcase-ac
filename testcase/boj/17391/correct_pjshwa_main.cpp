#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 300;
const int dx[2] = {1, 0}, dy[2] = {0, 1};
int A[MAX][MAX];
vector<pii> graph[MAX][MAX];
int cdist[MAX][MAX];

void solve() {
  int N, M;
  cin >> N >> M;
  for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) cin >> A[i][j];

  for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) {
    for (int d = 1; d <= A[i][j]; d++) {
      for (int k = 0; k < 2; k++) {
        int ni = i + dx[k] * d, nj = j + dy[k] * d;
        if (ni < 0 || ni >= N || nj < 0 || nj >= M) continue;
        graph[i][j].push_back({ni, nj});
      }
    }
  }

  memset(cdist, 0x3f, sizeof(cdist));
  queue<pii> q;
  cdist[0][0] = 0;
  q.push({0, 0});

  while (!q.empty()) {
    auto [i, j] = q.front(); q.pop();

    for (auto& [ni, nj] : graph[i][j]) {
      if (cdist[ni][nj] > cdist[i][j] + 1) {
        cdist[ni][nj] = cdist[i][j] + 1;
        q.push({ni, nj});
      }
    }
  }

  cout << cdist[N - 1][M - 1] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
