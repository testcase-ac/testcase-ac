#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 128;
int board[MAXN][MAXN], N;
int parent[MAXN];

int Find(int x) {
  if (x == parent[x]) return x;
  return parent[x] = Find(parent[x]);
}

void Union(int x, int y) {
  x = Find(x); y = Find(y);
  if (x != y) parent[x] = y;
}

bool is_identical(int si, int sj, int ti, int tj, int w) {
  if (w == 1) return board[si][sj] == board[ti][tj];

  bool ret = true;
  ret &= (is_identical(si, sj, ti, tj, w / 2));
  ret &= (is_identical(si, sj + w / 2, ti, tj + w / 2, w / 2));
  ret &= (is_identical(si + w / 2, sj, ti + w / 2, tj, w / 2));
  ret &= (is_identical(si + w / 2, sj + w / 2, ti + w / 2, tj + w / 2, w / 2));
  return ret;
}

bool is_homogeneous(int si, int sj, int w) {
  int v = board[si][sj], ok = 1;
  for (int i = si; i < si + w; ++i) for (int j = sj; j < sj + w; ++j) {
    ok &= (v == board[i][j]);
  }
  return ok;
}

// count total number of nodes
int f(int si, int sj, int w) {
  if (is_homogeneous(si, sj, w)) return 1;

  int ret = 1;
  ret += f(si, sj, w / 2);
  ret += f(si, sj + w / 2, w / 2);
  ret += f(si + w / 2, sj, w / 2);
  ret += f(si + w / 2, sj + w / 2, w / 2);
  return ret;
}

// count total number of nodes, connect the nodes if identical
int g(int si, int sj, int w) {
  if (is_homogeneous(si, sj, w)) return 1;

  iota(parent, parent + 4, 0);
  if (is_identical(si, sj, si, sj + w / 2, w / 2)) Union(0, 1);
  if (is_identical(si, sj, si + w / 2, sj + w / 2, w / 2)) Union(0, 2);
  if (is_identical(si, sj, si + w / 2, sj, w / 2)) Union(0, 3);
  if (is_identical(si, sj + w / 2, si + w / 2, sj + w / 2, w / 2)) Union(1, 2);
  if (is_identical(si, sj + w / 2, si + w / 2, sj, w / 2)) Union(1, 3);
  if (is_identical(si + w / 2, sj + w / 2, si + w / 2, sj, w / 2)) Union(2, 3);

  set<int> U;
  for (int i = 0; i < 4; ++i) U.insert(Find(i));

  int ret = 1;
  for (int u : U) {
    u = Find(u);
    cout << "w = " << w << ", u = " << u << '\n';
    if (u == 0) ret += g(si, sj, w / 2);
    if (u == 1) ret += g(si, sj + w / 2, w / 2);
    if (u == 2) ret += g(si + w / 2, sj + w / 2, w / 2);
    if (u == 3) ret += g(si + w / 2, sj, w / 2);
  }
  return ret;
}

void solve() {
  int on, om; cin >> on >> om;
  for (int i = 0; i < on; ++i) {
    string s; cin >> s;
    for (int j = 0; j < om; ++j) board[i][j] = s[j] - '0';
  }

  int n = 1, m = 1;
  while (n < on) n <<= 1;
  while (m < om) m <<= 1;
  N = max(n, m);

  int tot = f(0, 0, N);
  cout << tot << ' ';

  int w = N >> 1;
  for (int l = 1; w > 1; ++l) {

    iota(parent, parent + N, 0); int sit = 0;
    for (int sx = 0; sx < N; sx += w) for (int sy = 0; sy < N; sy += w) {

      int cit = 0;
      for (int cx = 0; cx < w; cx += w) for (int cy = 0; cy < w; cy += w) {
        if (is_identical(sx, sy, cx, cy, w)) Union(sit, cit);
        ++cit;
      }

      ++sit;
    }

    set<int> U;
    for (int it = 0; it < sit; ++it) U.insert(Find(it));
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
