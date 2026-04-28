#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 40;
int N, M;
char board[MAXN + 1][MAXN + 1];

void solve() {
  for (int i = 0; i < N; ++i) cin >> board[i];

  int C[26]{}, U[26][26]{}, minx[26], maxx[26], miny[26], maxy[26];
  fill(minx, minx + 26, MAXN); fill(maxx, maxx + 26, -1);
  fill(miny, miny + 26, MAXN); fill(maxy, maxy + 26, -1);

  for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) {
    if (board[i][j] == '.') continue;
    int c = board[i][j] - 'a'; ++C[c];
    minx[c] = min(minx[c], i); maxx[c] = max(maxx[c], i);
    miny[c] = min(miny[c], j); maxy[c] = max(maxy[c], j);
  }

  for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) {
    if (board[i][j] == '.') continue;
    int c = board[i][j] - 'a';
    for (int x = 0; x < 26; ++x) {
      if (x == c || C[x] == 0) continue;
      if (minx[x] <= i && i <= maxx[x] && miny[x] <= j && j <= maxy[x]) U[c][x] = 1;
    }
  }

  // Transitive closure
  for (int k = 0; k < 26; ++k) for (int i = 0; i < 26; ++i) for (int j = 0; j < 26; ++j) {
    U[i][j] |= U[i][k] & U[k][j];
  }

  cout << "Uncovered: ";
  for (int ci = 0; ci < 26; ++ci) {
    char c = 'a' + ci;
    int cnt = C[ci];
    if (cnt == 0) continue;

    int xlen = maxx[ci] - minx[ci] + 1, ylen = maxy[ci] - miny[ci] + 1;
    if (xlen * ylen != cnt) continue;

    int t_ok = 1;
    if (minx[ci] > 0) {
      int nx = minx[ci] - 1, ok = 1;
      for (int j = miny[ci]; j <= maxy[ci]; ++j) {
        char ch = board[nx][j];
        if (ch == '.' || ch == c || U[ci][ch - 'a']) ok = 0;
      }
      if (ok) t_ok = 0;
    }
    if (miny[ci] > 0) {
      int ny = miny[ci] - 1, ok = 1;
      for (int i = minx[ci]; i <= maxx[ci]; ++i) {
        char ch = board[i][ny];
        if (ch == '.' || ch == c || U[ci][ch - 'a']) ok = 0;
      }
      if (ok) t_ok = 0;
    }
    if (maxx[ci] < N - 1) {
      int nx = maxx[ci] + 1, ok = 1;
      for (int j = miny[ci]; j <= maxy[ci]; ++j) {
        char ch = board[nx][j];
        if (ch == '.' || ch == c || U[ci][ch - 'a']) ok = 0;
      }
      if (ok) t_ok = 0;
    }
    if (maxy[ci] < M - 1) {
      int ny = maxy[ci] + 1, ok = 1;
      for (int i = minx[ci]; i <= maxx[ci]; ++i) {
        char ch = board[i][ny];
        if (ch == '.' || ch == c || U[ci][ch - 'a']) ok = 0;
      }
      if (ok) t_ok = 0;
    }

    if (t_ok) cout << c;
  }
  cout << '\n';
}

int main() {
  fast_io();

  while (cin >> N >> M) {
    if (N == 0 && M == 0) break;
    solve();
  }
}
