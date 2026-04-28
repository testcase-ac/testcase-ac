#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 500;
char board[MAXN + 1][MAXN + 1];
int cdist[MAXN][MAXN][3], N, M;

bool oob(int i, int j) {
  return i < 0 || i >= N || j < 0 || j >= M;
}

bool is_valid(int i, int j, int type) {
  if (type == 0) return !oob(i, j) && board[i][j] != '0';
  else if (type == 1) {
    int cnt = 0;
    for (int k = 0; k < 3; ++k) {
      if (oob(i, j + k)) return false;
      cnt += board[i][j + k] != '0';
    }
    return cnt >= 2 || board[i][j + 1] != '0';
  }
  else if (type == 2) {
    int cnt = 0;
    for (int k = 0; k < 3; ++k) {
      if (oob(i + k, j)) return false;
      cnt += board[i + k][j] != '0';
    }
    return cnt >= 2 || board[i + 1][j] != '0';
  }
  return false;
}

bool is_finish(int i, int j, int type) {
  if (type == 0) return board[i][j] == '3';
  else if (type == 1) {
    for (int k = 0; k < 3; ++k) {
      if (!oob(i, j + k) && board[i][j + k] == '3') return true;
    }
  }
  else if (type == 2) {
    for (int k = 0; k < 3; ++k) {
      if (!oob(i + k, j) && board[i + k][j] == '3') return true;
    }
  }
  return false;
}

void solve() {
  cin >> N >> M;

  int si, sj;
  for (int i = 0; i < N; ++i) {
    cin >> board[i];
    for (int j = 0; j < M; ++j) {
      if (board[i][j] == '2') si = i, sj = j;
    }
  }

  memset(cdist, 0x3f, sizeof(cdist));
  using T = tuple<int, int, int>; queue<T> Q;
  Q.emplace(si, sj, 0); cdist[si][sj][0] = 0;

  while (!Q.empty()) {
    auto [i, j, type] = Q.front(); Q.pop();
    if (is_finish(i, j, type)) {
      cout << cdist[i][j][type] << '\n';
      return;
    }

    if (type == 0) {
      if (is_valid(i - 3, j, 2) && cdist[i - 3][j][2] > cdist[i][j][0] + 1) {
        cdist[i - 3][j][2] = cdist[i][j][0] + 1;
        Q.emplace(i - 3, j, 2);
      }
      if (is_valid(i, j - 3, 1) && cdist[i][j - 3][1] > cdist[i][j][0] + 1) {
        cdist[i][j - 3][1] = cdist[i][j][0] + 1;
        Q.emplace(i, j - 3, 1);
      }
      if (is_valid(i + 1, j, 2) && cdist[i + 1][j][2] > cdist[i][j][0] + 1) {
        cdist[i + 1][j][2] = cdist[i][j][0] + 1;
        Q.emplace(i + 1, j, 2);
      }
      if (is_valid(i, j + 1, 1) && cdist[i][j + 1][1] > cdist[i][j][0] + 1) {
        cdist[i][j + 1][1] = cdist[i][j][0] + 1;
        Q.emplace(i, j + 1, 1);
      }
    }
    else if (type == 1) {
      if (is_valid(i - 1, j, 1) && cdist[i - 1][j][1] > cdist[i][j][1] + 1) {
        cdist[i - 1][j][1] = cdist[i][j][1] + 1;
        Q.emplace(i - 1, j, 1);
      }
      if (is_valid(i, j - 1, 0) && cdist[i][j - 1][0] > cdist[i][j][1] + 1) {
        cdist[i][j - 1][0] = cdist[i][j][1] + 1;
        Q.emplace(i, j - 1, 0);
      }
      if (is_valid(i + 1, j, 1) && cdist[i + 1][j][1] > cdist[i][j][1] + 1) {
        cdist[i + 1][j][1] = cdist[i][j][1] + 1;
        Q.emplace(i + 1, j, 1);
      }
      if (is_valid(i, j + 3, 0) && cdist[i][j + 3][0] > cdist[i][j][1] + 1) {
        cdist[i][j + 3][0] = cdist[i][j][1] + 1;
        Q.emplace(i, j + 3, 0);
      }
    }
    else if (type == 2) {
      if (is_valid(i - 1, j, 0) && cdist[i - 1][j][0] > cdist[i][j][2] + 1) {
        cdist[i - 1][j][0] = cdist[i][j][2] + 1;
        Q.emplace(i - 1, j, 0);
      }
      if (is_valid(i, j - 1, 2) && cdist[i][j - 1][2] > cdist[i][j][2] + 1) {
        cdist[i][j - 1][2] = cdist[i][j][2] + 1;
        Q.emplace(i, j - 1, 2);
      }
      if (is_valid(i + 3, j, 0) && cdist[i + 3][j][0] > cdist[i][j][2] + 1) {
        cdist[i + 3][j][0] = cdist[i][j][2] + 1;
        Q.emplace(i + 3, j, 0);
      }
      if (is_valid(i, j + 1, 2) && cdist[i][j + 1][2] > cdist[i][j][2] + 1) {
        cdist[i][j + 1][2] = cdist[i][j][2] + 1;
        Q.emplace(i, j + 1, 2);
      }
    }
  }

  cout << "-2\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
