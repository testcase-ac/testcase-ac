#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1000;
const int dx[] = {0, 0, 1, -1}, dy[] = {1, -1, 0, 0};
const int DMG_NORMAL = 1, DMG_STRONG = 2;

char board[MAXN + 1][MAXN + 1];
int D[MAXN][MAXN];

void mark_as_destroyed(int i, int j) {
  board[i][j] = 'x';
}

bool is_blockage(int i, int j) {
  return board[i][j] == '|';
}

bool is_normal_building(int i, int j) {
  return board[i][j] == '*';
}

bool is_strong_building(int i, int j) {
  return board[i][j] == '#';
}

bool is_destroyed(int i, int j) {
  return board[i][j] == 'x';
}

bool add_damage(int i, int j) {
  ++D[i][j]; bool dest = 0;
  dest |= (is_normal_building(i, j) && D[i][j] >= DMG_NORMAL);
  dest |= (is_strong_building(i, j) && D[i][j] >= DMG_STRONG);
  if (dest) mark_as_destroyed(i, j);
  return dest;
}

void solve() {
  int N, M; cin >> N >> M;
  for (int i = 0; i < N; ++i) cin >> board[i];
  
  int tot = 0, oi, oj;
  for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) {
    tot += (board[i][j] == '*' || board[i][j] == '#');
    if (board[i][j] == '@') oi = i, oj = j;
  }

  auto oob = [&](int i, int j) {
    return i < 0 || i >= N || j < 0 || j >= M;
  };

  queue<pii> Q;
  for (int k = 0; k < 4; ++k) {
    for (int t = 1; t <= 2; ++t) {
      int ni = oi + dx[k] * t, nj = oj + dy[k] * t;
      if (oob(ni, nj) || is_blockage(ni, nj)) break;
      if (add_damage(ni, nj)) Q.emplace(ni, nj);
    }
  }

  while (!Q.empty()) {
    auto [i, j] = Q.front(); Q.pop();
    for (int k = 0; k < 4; ++k) {
      int ni = i + dx[k], nj = j + dy[k];
      if (oob(ni, nj) || is_blockage(ni, nj)) continue;
      if (add_damage(ni, nj)) Q.emplace(ni, nj);
    }
  }

  int brk = 0;
  for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) {
    brk += is_destroyed(i, j);
  }
  cout << brk << ' ' << tot - brk << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
