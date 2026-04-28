#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1000, INF = 0x3f3f3f3f;
const int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};
int A[MAX][MAX], d[MAX][MAX];
int N, M;

int r(int i, int j) {
  if (d[i][j] != -1) return d[i][j];

  set<int> u;
  for (int k = 0; k < 4; k++) {
    int x = i + dx[k], y = j + dy[k];
    if (x < 0 || x >= N || y < 0 || y >= M) continue;
    if (A[x][y] >= A[i][j]) continue;
    u.insert(r(x, y));
  }

  int ret;
  if (u.size() > 1) ret = INF;
  else if (u.size() == 1) ret = *u.begin();
  else ret = A[i][j];

  return d[i][j] = ret;
}

void solve() {
  cin >> N >> M;

  priority_queue<tii, vector<tii>, greater<tii>> pq;
  for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) {
    cin >> A[i][j];
    pq.push({A[i][j], i, j});
  }

  memset(d, -1, sizeof(d));
  while (!pq.empty()) {
    auto [v, i, j] = pq.top(); pq.pop();
    r(i, j);
  }

  // for (int i = 0; i < N; i++) {
  //   for (int j = 0; j < M; j++) {
  //     cout << d[i][j] << " ";
  //   }
  //   cout << endl;
  // }

  int ans = 0;
  for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) {
    if (d[i][j] == INF) ans++;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
