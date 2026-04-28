#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 100;
const int dx[] = {0, 0, 1, -1};
const int dy[] = {1, -1, 0, 0};
char board[MAXN][MAXN]; int D[MAXN][MAXN];
int N, M, ei, ej; string S;
vector<pii> adj[MAXN][MAXN];
int indegree[MAXN][MAXN], vis[MAXN][MAXN];
int indegree_c[MAXN][MAXN];

void copy_indegree() {
  for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) indegree_c[i][j] = indegree[i][j];
}

void print() {
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < M; ++j) cout << board[i][j];
    cout << '\n';
  }
}

bool is_start_spot(char c) {
  return 'A' <= c && c <= 'Z';
}

bool is_empty_spot(char c) {
  return c == ' ' || c == 0 || c == '\n';
}

bool is_terminal_spot(char c) {
  return c == ':' || c == '?';
}

void init() {
  for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) {
    adj[i][j].clear(); indegree[i][j] = vis[i][j] = 0;
    if (board[i][j] == '?') ei = i, ej = j;
  }

  queue<pii> Q;
  for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) {
    if (is_start_spot(board[i][j])) Q.push({i, j}), vis[i][j] = 1;
  }

  while (!Q.empty()) {
    auto [i, j] = Q.front(); Q.pop();
    // cout << "i = " << i << ", j = " << j << '\n';
    // cout << "board[i][j] = " << board[i][j] << '\n';

    if (board[i][j] == ':') {
      for (auto [ni, nj] : {pii{i - 1, j + 2}, pii{i + 1, j + 2}}) {
        if (ni < 0 || ni >= N || nj < 0 || nj >= M) continue;
        if (board[ni][nj] == '>' || board[ni][nj] == ')') {
          ++indegree[ni][nj];
          adj[i][j].push_back({ni, nj});
          if (!vis[ni][nj]) Q.push({ni, nj}), vis[ni][nj] = 1;
        }
      }
    } else {
      for (int k = 0; k < 4; ++k) {
        int ni = i + dx[k], nj = j + dy[k];
        if (ni < 0 || ni >= N || nj < 0 || nj >= M) continue;
        if (vis[ni][nj] || is_empty_spot(board[ni][nj])) continue;

        ++indegree[ni][nj];
        adj[i][j].push_back({ni, nj});
        Q.push({ni, nj}); vis[ni][nj] = 1;
      }
    }
  }
}

void solve() {
  memset(D, -1, sizeof(D));
  queue<pii> Q; copy_indegree();
  for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) {
    if (!is_start_spot(board[i][j])) continue;
    D[i][j] = S[board[i][j] - 'A'] - '0';
    assert(indegree_c[i][j] == 0);
    Q.push({i, j});
  }

  while (!Q.empty()) {
    auto [i, j] = Q.front(); Q.pop();
    // cout << "i = " << i << ", j = " << j << '\n';
    // cout << "board[i][j] = " << board[i][j] << ", D[i][j] = " << D[i][j] << '\n';

    for (auto& [ni, nj] : adj[i][j]) {
      if (board[ni][nj] == 'o') D[ni][nj] = 1 - D[i][j];
      else if (board[ni][nj] == ')') {
        if (D[ni][nj] == -1) D[ni][nj] = D[i][j];
        else D[ni][nj] &= D[i][j];
      }
      else if (board[ni][nj] == '>') {
        if (D[ni][nj] == -1) D[ni][nj] = D[i][j];
        else D[ni][nj] |= D[i][j];
      }
      else D[ni][nj] = D[i][j];
      if (!--indegree_c[ni][nj]) Q.push({ni, nj});
    }
  }

  cout << D[ei][ej] << '\n';
}

int main() {
  fast_io();

  // get line until end of file
  int flag = 0;
  while (getline(cin, S)) {
    if (flag == 2) cout << '\n', flag = 0;
    if (flag == 0) {
      if (S[0] == '*') {
        flag = 1;
        init();
      } else {
        int Z = S.size(); M = max(M, Z);
        for (int i = 0; i < Z; ++i) board[N][i] = S[i];
        ++N;
      }
    } else if (flag == 1) {
      if (S[0] == '*') {
        flag = 2;
        N = M = 0;
        memset(board, 0, sizeof(board));
      }
      else solve();
    }
  }
}
