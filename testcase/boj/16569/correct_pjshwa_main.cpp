#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 100, INF = 0x3f3f3f3f;
const int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};
int H[MAX][MAX], vdist[MAX][MAX], cdist[MAX][MAX];
bool vc[MAX][MAX];

void solve() {
  int N, M, V, X, Y;
  cin >> N >> M >> V >> X >> Y;
  X--; Y--;
  for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) cin >> H[i][j];
  
  priority_queue<tii, vector<tii>, greater<tii>> pq;
  for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) {
    vdist[i][j] = cdist[i][j] = INF;
  }
  while (V--) {
    int xi, yi, ti;
    cin >> xi >> yi >> ti;
    xi--; yi--;
    pq.push({ti, xi, yi});
    vdist[xi][yi] = ti;
    vc[xi][yi] = true;
  }

  while (!pq.empty()) {
    auto [w, ui, uj] = pq.top();
    pq.pop();

    if (w > vdist[ui][uj]) continue;

    for (int k = 0; k < 4; k++) {
      int ni = ui + dx[k], nj = uj + dy[k];
      if (ni < 0 || ni >= N || nj < 0 || nj >= M) continue;

      if (vdist[ni][nj] > vdist[ui][uj] + 1) {
        vdist[ni][nj] = vdist[ui][uj] + 1;
        pq.push({vdist[ni][nj], ni, nj});
      }
    }
  }

  queue<pii> q;
  q.push({X, Y});
  cdist[X][Y] = 0;

  while (!q.empty()) {
    auto [xi, yi] = q.front(); q.pop();

    for (int k = 0; k < 4; k++) {
      int ni = xi + dx[k], nj = yi + dy[k];
      if (ni < 0 || ni >= N || nj < 0 || nj >= M) continue;
      if (vc[ni][nj]) continue;
      if (vdist[ni][nj] <= cdist[xi][yi] + 1) continue;

      if (cdist[ni][nj] > cdist[xi][yi] + 1) {
        cdist[ni][nj] = cdist[xi][yi] + 1;
        q.push({ni, nj});
      }
    }
  }

  int mval = 0, mtime = 0;
  for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) {
    if (cdist[i][j] == INF) continue;
    if (mval < H[i][j]) {
      mval = H[i][j];
      mtime = cdist[i][j];
    }
    else if (mval == H[i][j] && mtime > cdist[i][j]) {
      mtime = cdist[i][j];
    }
  }

  cout << mval << ' ' << mtime << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
