#include <bits/stdc++.h>
using namespace std;
#define all(v) v.begin(), v.end()
#define compress(v) sort(all(v)), v.erase(unique(all(v)), v.end())

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2500;
const int dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};
int board[MAX][MAX];
int dt[MAX][MAX];
bool vis[MAX][MAX];
int NW, NH;

void dfs(int i, int j) {
  vis[i][j] = 1;
  for (int k = 0; k < 4; k++) {
    int nx = i + dx[k], ny = j + dy[k];
    if (nx < 0 || nx >= NW || ny < 0 || ny >= NH) continue;
    if (vis[nx][ny] || board[nx][ny]) continue;
    dfs(nx, ny);
  }
}

void solve() {
  int W, H;
  cin >> W >> H;
  vector<int> xs = {0, W}, ys = {0, H};

  int N;
  cin >> N;
  vector<tuple<int, int, int, int>> v;
  for (int i = 0; i < N; i++) {
    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    xs.push_back(x1); xs.push_back(x2);
    ys.push_back(y1); ys.push_back(y2);
    v.push_back({x1, y1, x2, y2});
  }

  compress(xs);
  compress(ys);
  map<int, int> xv, yv;
  for (int i = 0; i < xs.size(); i++) xv[xs[i]] = i;
  for (int i = 0; i < ys.size(); i++) yv[ys[i]] = i;

  for (auto [x1, y1, x2, y2] : v) {
    int x1i = xv[x1], x2i = xv[x2];
    int y1i = yv[y1], y2i = yv[y2];

    dt[x1i][y1i]++;
    dt[x2i][y1i]--;
    dt[x1i][y2i]--;
    dt[x2i][y2i]++;
  }

  for (int i = 0; i < MAX; i++) for (int j = 0; j < MAX; j++) {
    if (i == 0 && j == 0) board[i][j] = dt[i][j];
    else if (i == 0) board[i][j] = board[i][j - 1] + dt[i][j];
    else if (j == 0) board[i][j] = board[i - 1][j] + dt[i][j];
    else board[i][j] = board[i - 1][j] + board[i][j - 1] - board[i - 1][j - 1] + dt[i][j];
  }

  NW = xv[W], NH = yv[H];
  int cc = 0;
  for (int i = 0; i < NW; i++) for (int j = 0; j < NH; j++) {
    if (vis[i][j] || board[i][j]) continue;
    cc++;
    dfs(i, j);
  }
  cout << cc << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
