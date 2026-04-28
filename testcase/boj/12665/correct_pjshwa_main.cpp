#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 5;
const int dx[9] = {0, 0, 1, -1, 1, 1, -1, -1, 0};
const int dy[9] = {1, -1, 0, 0, 1, -1, 1, -1, 0};
int R, C, B[MAXN][MAXN], ans;
vector<int> cur;

bool is_valid_row(int i) {
  for (int j = 0; j < C; ++j) {
    int cnt = 0;
    for (int d = 0; d < 9; ++d) {
      int ni = i + dx[d], nj = j + dy[d];
      if (ni < 0 || ni >= R || nj < 0 || nj >= C) continue;
      cnt += (cur[ni] & (1 << nj)) > 0;
    }
    if (cnt != B[i][j]) return false;
  }
  return true;
}

void dfs(int i) {
  if (i == R - 1) {
    if (is_valid_row(i)) {
      ans = max(ans, __builtin_popcount(cur[R / 2]));
    }
    return;
  }

  for (int s = 0; s < (1 << C); ++s) {
    cur.push_back(s);
    if (is_valid_row(i)) dfs(i + 1);
    cur.pop_back();
  }
}

int tc;
void solve() {
  cout << "Case #" << ++tc << ": ";

  cin >> R >> C;
  for (int i = 0; i < R; ++i) for (int j = 0; j < C; ++j) cin >> B[i][j];

  cur.clear(); ans = -1;
  for (int s = 0; s < (1 << C); ++s) {
    cur.push_back(s);
    dfs(0);
    cur.pop_back();
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
