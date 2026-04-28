#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1000, INF = 0x3f3f3f3f;
const int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};
int S[MAX][MAX], cdist[MAX][MAX];
int N, M;

void dijk() {
  for (int i = 0; i < N; i++) fill(cdist[i], cdist[i] + M, INF);

  priority_queue<tii, vector<tii>, greater<tii>> pq;
  for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) {
    if (i == 0 || j == 0 || j == M - 1) {
      cdist[i][j] = S[i][j];
      pq.push({S[i][j], i, j});
    }
  }

  while (!pq.empty()) {
    auto [w, ui, uj] = pq.top();
    pq.pop();

    if (w > cdist[ui][uj]) continue;

    for (int k = 0; k < 4; k++) {
      int vi = ui + dx[k], vj = uj + dy[k];
      if (vi < 0 || vi >= N || vj < 0 || vj >= M) continue;

      int nw = max(S[vi][vj], w);
      if (nw < cdist[vi][vj]) {
        cdist[vi][vj] = nw;
        pq.push({nw, vi, vj});
      }
    }
  }
}

void solve() {
  int K;
  cin >> N >> M >> K;
  for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) cin >> S[i][j];

  dijk();

  map<int, int> t;
  for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) t[cdist[i][j]]++;

  int lval = 0;
  for (auto& [k, v] : t) {
    lval += v;
    if (lval >= K) {
      cout << k << '\n';
      return;
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
