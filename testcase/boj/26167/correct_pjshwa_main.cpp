#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 500;
const int dx[] = {0, 0, 1, -1}, dy[] = {1, -1, 0, 0};
int A[MAXN][MAXN], N, M;

vector<pii> cur;
vector<vector<pii>> sets;

void dfs(int t) {
  auto cur2 = cur;
  if (t == 6) {
    sets.push_back(cur2);
    return;
  }

  for (auto& [x, y] : cur2) {
    for (int k = 0; k < 4; ++k) {
      int nx = x + dx[k], ny = y + dy[k];
      if (cur.end() != find(cur.begin(), cur.end(), make_pair(nx, ny))) continue;
      cur.push_back({nx, ny});
      dfs(t + 1);
      cur.pop_back();
    }
  }
}

void solve() {
  cin >> N >> M;
  for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) cin >> A[i][j];

  int ans = 0;
  for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) {
    for (auto& set : sets) {
      int ok = 1, cur = 0;
      for (auto& [x, y] : set) {
        int nx = i + x, ny = j + y;
        if (nx < 0 || nx >= N || ny < 0 || ny >= M) {
          ok = 0;
          break;
        }
        cur += A[nx][ny];
      }
      if (ok) ans = max(ans, cur);
    }
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  cur.emplace_back(0, 0);
  dfs(1);

  for (auto& c : sets) {
    sort(c.begin(), c.end());
    auto [dx, dy] = c[0];
    for (auto& [x, y] : c) x -= dx, y -= dy;
  }
  sort(sets.begin(), sets.end());
  sets.erase(unique(sets.begin(), sets.end()), sets.end());

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
