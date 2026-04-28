#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 600;
const int dx[9] = {0, 0, 0, 1, 1, 1, -1, -1, -1};
const int dy[9] = {0, 1, -1, 0, 1, -1, 0, 1, -1};
char board[MAXN + 1][MAXN + 1], res[MAXN + 1][MAXN + 1];
int N, M;

void dfs2(int j);
void print_res() {
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < M; ++j) cout << res[i][j];
    cout << '\n';
  }
}

void dfs1(int i) {
  if (i == N) {
    dfs2(2);
    return;
  }

  for (int c = 0; c < 4; ++c) {
    if (c & 1) res[i][0] = 'X';
    if (c & 2) res[i][1] = 'X';

    int ok = 1;
    if (i > 0) {
      int target = board[i - 1][0] - '0', cnt = 0;
      for (int k = 0; k < 9; ++k) {
        int x = i - 1 + dx[k], y = 0 + dy[k];
        if (x < 0 || x >= N || y < 0 || y >= M) continue;
        if (res[x][y] == 'X') ++cnt;
      }
      if (cnt != target) ok = 0;
    }
    if (ok) dfs1(i + 1);

    if (c & 1) res[i][0] = '.';
    if (c & 2) res[i][1] = '.';
  }
}

void dfs2(int j) {
  cout << "j = " << j << '\n';

  if (j == M) {
    int ok = 1;
    for (int i = 0; i < N; ++i) {
      int target = board[i][j - 1] - '0', cnt = 0;
      for (int k = 0; k < 9; ++k) {
        int x = i + dx[k], y = j - 1 + dy[k];
        if (x < 0 || x >= N || y < 0 || y >= M) continue;
        if (res[x][y] == 'X') ++cnt;
      }
      if (cnt != target) {
        ok = 0;
        break;
      }
    }
    if (ok) {
      // write res to 22206.txt
      ofstream fout("22206.txt");
      for (int i = 0; i < N; ++i) fout << res[i] << '\n';
      fout.close();
      exit(0);
    }
    return;
  }

  for (int s = 0; s < (1 << N); ++s) {
    for (int i = 0; i < N; ++i) {
      if (s & (1 << i)) res[i][j] = 'X';
      else res[i][j] = '.';
    }

    int ok = 1;
    for (int i = 0; i < N; ++i) {
      int target = board[i][j - 1] - '0', cnt = 0;
      for (int k = 0; k < 9; ++k) {
        int x = i + dx[k], y = j - 1 + dy[k];
        if (x < 0 || x >= N || y < 0 || y >= M) continue;
        if (res[x][y] == 'X') ++cnt;
      }
      if (cnt != target) {
        ok = 0;
        break;
      }
    }
    if (ok) {
      print_res();
      dfs2(j + 1);
    }

    for (int i = 0; i < N; ++i) res[i][j] = '.';
  }
}

void solve() {
  cin >> N >> M;
  for (int i = 0; i < N; ++i) {
    cin >> board[i];
    fill(res[i], res[i] + M, '.');
  }
  dfs1(0);
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
