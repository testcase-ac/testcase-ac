#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 50;
const int dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};
char board[MAX + 1][MAX + 1];
int parent[MAX * MAX], usz[MAX * MAX];
int N, M;

int Find(int x) {
  if (x == parent[x]) return x;
  else {
    int p = Find(parent[x]);
    parent[x] = p;
    return p;
  }
}

void Union(int x, int y) {
  x = Find(x);
  y = Find(y);

  if (x == y) return;

  parent[y] = x;
  usz[x] += usz[y];
}

void solve() {
  for (int i = 0; i < N; i++) cin >> board[i];
  for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) {
    parent[i * M + j] = i * M + j;
    usz[i * M + j] = 1;
  }
  for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) {
    if (board[i][j] != '.') continue;
    for (int k = 0; k < 4; k++) {
      int nx = i + dx[k], ny = j + dy[k];
      if (nx < 0 || nx >= N || ny < 0 || ny >= M) continue;
      if (board[nx][ny] == '.') Union(i * M + j, nx * M + ny);
    }
  }

  set<int> w, b, u;
  for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) {
    if (board[i][j] != '.') continue;

    for (int k = 0; k < 4; k++) {
      int nx = i + dx[k], ny = j + dy[k];
      if (nx < 0 || nx >= N || ny < 0 || ny >= M) continue;

      int g = Find(i * M + j);
      if (u.count(g)) continue;

      if (board[nx][ny] == 'W') {
        if (b.count(g)) {
          b.erase(g);
          u.insert(g);
        }
        else w.insert(g);
      }
      if (board[nx][ny] == 'B') {
        if (w.count(g)) {
          w.erase(g);
          u.insert(g);
        }
        else b.insert(g);
      }
    }
  }

  int bsz = 0, wsz = 0;
  for (int g : b) bsz += usz[g];
  for (int g : w) wsz += usz[g];
  cout << bsz << ' ' << wsz << '\n';
}

int main() {
  fast_io();

  while (1) {
    cin >> M >> N;
    if (N == 0 && M == 0) break;
    solve();
  }
}
