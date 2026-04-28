#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int N = 20, INF = 0x3f3f3f3f;
const int dx[] = {0, 1, 0, -1}, dy[] = {1, 0, -1, 0};

string S[N];
bool vis[N][N];
vector<vector<pii>> chunks;
vector<pii> cur;

void dfs(int i, int j) {
  cur.emplace_back(i, j);
  vis[i][j] = true;
  for (int k = 0; k < 4; ++k) {
    int ni = i + dx[k], nj = j + dy[k];
    if (ni < 0 || ni >= N || nj < 0 || nj >= N) continue;
    if (S[ni][nj] == '.' || vis[ni][nj]) continue;
    dfs(ni, nj);
  }
}

int B[5][5], Z;
vector<vector<pii>> cbases;
vector<pii> cbase;

void dfs_f(int idx) {
  if (idx == Z) {
    cbases.emplace_back(cbase);
    return;
  }

  for (int i = 0; i < 5; ++i) for (int j = 0; j < 5; ++j) {
    auto [bx, by] = chunks[idx][0]; bool ok = true;
    for (auto& [x, y] : chunks[idx]) {
      int nx = x - bx + i, ny = y - by + j;
      if (nx < 0 || nx >= 5 || ny < 0 || ny >= 5 || B[nx][ny]) {
        ok = false;
        break;
      }
    }

    if (ok) {
      cbase.emplace_back(i, j);
      for (auto& [x, y] : chunks[idx]) {
        int nx = x - bx + i, ny = y - by + j;
        B[nx][ny] = 1;
      }
      dfs_f(idx + 1);
      for (auto& [x, y] : chunks[idx]) {
        int nx = x - bx + i, ny = y - by + j;
        B[nx][ny] = 0;
      }
      cbase.pop_back();
    }
  }
}

int tc;
void solve() {
  cout << "Case " << ++tc << ": ";

  memset(vis, 0, sizeof(vis));
  chunks.clear(); cbases.clear();

  for (int i = 0; i < N; ++i) cin >> S[i];

  for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) {
    if (S[i][j] == '.' || vis[i][j]) continue;

    cur.clear();
    dfs(i, j);
    chunks.emplace_back(cur);
  }
  for (auto& C : chunks) sort(C.begin(), C.end());

  Z = chunks.size();
  dfs_f(0);
  if (cbases.empty()) return cout << "invalid data\n", void();

  int ans = INF;
  for (int i = 0; i <= 15; ++i) for (int j = 0; j <= 15; ++j) {
    for (auto& cbase : cbases) {
      int cur = 0;
      for (int k = 0; k < Z; ++k) {
        auto [bx, by] = cbase[k];
        bx += i, by += j;

        auto [cx, cy] = chunks[k][0];
        cur += abs(bx - cx) + abs(by - cy);
      }
      ans = min(ans, cur);
    }
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
