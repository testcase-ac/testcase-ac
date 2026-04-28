#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1000;
const int dx[] = {0, 1, 0, -1}, dy[] = {1, 0, -1, 0};
char board[MAXN + 1][MAXN + 1];
vector<pii> C; int N;

void dfs(int i, int j, int pi, int pj, char c) {
  C.emplace_back(i, j);
  for (int k = 0; k < 4; ++k) {
    int ni = i + dx[k], nj = j + dy[k];
    if (ni == pi && nj == pj) continue;
    if (ni < 0 || ni >= N || nj < 0 || nj >= N) continue;
    if (board[ni][nj] != c) continue;
    dfs(ni, nj, i, j, c);
  }
}

void solve() {
  int T; cin >> N >> T;
  for (int i = 0; i < N; ++i) cin >> board[i];

  deque<pii> dq[26]; int dir[26];
  for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) {
    char c = board[i][j];
    if (!(c >= 'A' && c <= 'Z')) continue;

    C.clear();
    dfs(i, j, -1, -1, c + 32);
    for (auto [i, j] : C) dq[c - 'A'].emplace_back(i, j);

    auto [fi, fj] = dq[c - 'A'][0];
    auto [si, sj] = dq[c - 'A'][1];
    for (int k = 0; k < 4; ++k) {
      int di = fi - si, dj = fj - sj;
      if (di == dx[k] && dj == dy[k]) {
        dir[c - 'A'] = k;
        break;
      }
    }
  }

  auto is_block = [&](int i, int j) {
    if (i < 0 || i >= N || j < 0 || j >= N) return true;
    return board[i][j] != '.';
  };
  auto move_snake = [&](int c) {
    auto [i, j] = dq[c].front();
    int ni = i + dx[dir[c]], nj = j + dy[dir[c]];
    if (is_block(ni, nj)) {
      dir[c] = (dir[c] + 1) % 4;
      ni = i + dx[dir[c]], nj = j + dy[dir[c]];
      if (is_block(ni, nj)) {
        dir[c] = (dir[c] + 2) % 4;
        ni = i + dx[dir[c]], nj = j + dy[dir[c]];
        if (is_block(ni, nj)) {
          dir[c] = (dir[c] + 1) % 4;
          return;
        }
      }
    }

    auto [bi, bj] = dq[c].back(); dq[c].pop_back();
    board[bi][bj] = '.';
    dq[c].push_front({ni, nj});
    board[ni][nj] = c + 'A'; board[i][j] = c + 'a';
  };

  while (T--) {
    for (int c = 0; c < 26; ++c) if (!dq[c].empty()) move_snake(c);
  }

  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) cout << board[i][j];
    cout << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
