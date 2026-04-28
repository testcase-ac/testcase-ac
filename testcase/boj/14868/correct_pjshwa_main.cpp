#include <bits/stdc++.h>
#define pii pair<int, int>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int board[2001][2001], parent[100001];

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

  if (x != y) parent[y] = x;
}

int main() {
  fast_io();

  int N, k, a, b;
  cin >> N >> k;
  vector<pii> cvs;

  for (int i = 1; i <= k; i++) {
    cin >> a >> b;
    parent[i] = i;
    board[a - 1][b - 1] = i;
    cvs.push_back({a - 1, b - 1});
  }

  for (auto [i, j] : cvs) {
    if (i > 0 && board[i - 1][j]) {
      if (Find(board[i][j]) != Find(board[i - 1][j])) {
        k--;
        Union(board[i][j], board[i - 1][j]);
      }
    }
    if (i < N - 1 && board[i + 1][j]) {
      if (Find(board[i][j]) != Find(board[i + 1][j])) {
        k--;
        Union(board[i][j], board[i + 1][j]);
      }
    }
    if (j > 0 && board[i][j - 1]) {
      if (Find(board[i][j]) != Find(board[i][j - 1])) {
        k--;
        Union(board[i][j], board[i][j - 1]);
      }
    }
    if (j < N - 1 && board[i][j + 1]) {
      if (Find(board[i][j]) != Find(board[i][j + 1])) {
        k--;
        Union(board[i][j], board[i][j + 1]);
      }
    }
  }

  queue<tuple<pii, int, int>> q;
  for (auto [i, j] : cvs) q.push({{i, j}, board[i][j], 0});

  while (!q.empty()) {
    auto[p, o, d] = q.front();
    auto[pi, pj] = p;
    q.pop();

    if (d && board[pi][pj]) continue;
    board[pi][pj] = o;

    if (pi > 0) {
      if (board[pi - 1][pj]) {
        if (Find(o) != Find(board[pi - 1][pj])) {
          k--;
          Union(o, board[pi - 1][pj]);
        }
      }
      else q.push({{pi - 1, pj}, o, d + 1});
    }
    if (pi < N - 1) {
      if (board[pi + 1][pj]) {
        if (Find(o) != Find(board[pi + 1][pj])) {
          k--;
          Union(o, board[pi + 1][pj]);
        }
      }
      else q.push({{pi + 1, pj}, o, d + 1});
    }
    if (pj > 0) {
      if (board[pi][pj - 1]) {
        if (Find(o) != Find(board[pi][pj - 1])) {
          k--;
          Union(o, board[pi][pj - 1]);
        }
      }
      else q.push({{pi, pj - 1}, o, d + 1});
    }
    if (pj < N - 1) {
      if (board[pi][pj + 1]) {
        if (Find(o) != Find(board[pi][pj + 1])) {
          k--;
          Union(o, board[pi][pj + 1]);
        }
      }
      else q.push({{pi, pj + 1}, o, d + 1});
    }

    if (k == 1) {
      cout << d;
      break;
    }
  }
}
