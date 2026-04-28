#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 25, INF = 0x3f3f3f3f;
const int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};
int board[MAX][MAX];
vector<tii> graph[MAX][MAX];
int cdist[MAX][MAX], odist[MAX][MAX];
int N, M;

void dijk(int si, int sj) {
  for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) cdist[i][j] = INF;

  priority_queue<tii, vector<tii>, greater<tii>> pq;
  pq.push({0, si, sj});
  cdist[si][sj] = 0;

  while (!pq.empty()) {
    auto [w, ui, uj] = pq.top();
    pq.pop();

    if (w > cdist[ui][uj]) continue;

    for (auto [vi, vj, d] : graph[ui][uj]) {
      if (cdist[vi][vj] > w + d) {
        cdist[vi][vj] = w + d;
        pq.push({w + d, vi, vj});
      }
    }
  }
}

void solve() {
  int T, D;
  cin >> N >> M >> T >> D;
  for (int i = 0; i < N; i++) {
    string s;
    cin >> s;
    for (int j = 0; j < M; j++) {
      if (isupper(s[j])) board[i][j] = s[j] - 'A';
      else board[i][j] = s[j] - 'a' + 26;
    }
  }

  for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) {
    for (int k = 0; k < 4; k++) {
      int ni = i + dx[k], nj = j + dy[k];
      if (ni < 0 || ni >= N || nj < 0 || nj >= M) continue;

      int diff = board[ni][nj] - board[i][j];
      if (abs(diff) > T) continue;

      if (diff > 0) graph[i][j].push_back({ni, nj, diff * diff});
      else graph[i][j].push_back({ni, nj, 1});
    }
  }

  for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) {
    dijk(i, j);
    odist[i][j] = cdist[0][0];
  }

  dijk(0, 0);
  int ans = board[0][0];
  for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) {
    if (i == 0 && j == 0) continue;
    if (cdist[i][j] + odist[i][j] <= D) ans = max(ans, board[i][j]);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
