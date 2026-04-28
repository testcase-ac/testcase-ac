#include <bits/stdc++.h>
using namespace std;
using ll = long long;
 
void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1000;
const int dx[] = {0, 1, 0, -1}, dy[] = {1, 0, -1, 0};
char board[MAXN + 1][MAXN + 1];
char O[MAXN + 1][MAXN + 1];
int N, M, f = 0;

void drill_right_1(int si, int sj, int ei, int ej) {
  for (int i = 0; i < 5; ++i) {
    if (board[6 * si + i][6 * sj + 4] != '.') continue;
    if (board[6 * ei + i][6 * ej + 0] != '.') continue;
    if (board[6 * ei + i][6 * ej + 1] != '.') continue;

    board[6 * si + i][6 * sj + 4] = 'z' - f;
    board[6 * si + i][6 * sj + 5] = '_';
    board[6 * ei + i][6 * ej + 0] = 'z' - f;
    board[6 * ei + i][6 * ej + 1] = 'z' - f;
    break;
  }
}

void drill_right_2(int si, int sj, int ei, int ej) {
  for (int i = 0; i < 5; ++i) {
    if (board[6 * si + i][6 * sj + 3] != '.') continue;
    if (board[6 * si + i][6 * sj + 4] != '.') continue;
    if (board[6 * ei + i][6 * ej + 0] != '.') continue;

    board[6 * si + i][6 * sj + 3] = 'z' - f;
    board[6 * si + i][6 * sj + 4] = 'z' - f;
    board[6 * si + i][6 * sj + 5] = '_';
    board[6 * ei + i][6 * ej + 0] = 'z' - f;
    break;
  }
}

void drill_left_1(int si, int sj, int ei, int ej) {
  for (int i = 0; i < 5; ++i) {
    if (board[6 * si + i][6 * sj + 0] != '.') continue;
    if (board[6 * ei + i][6 * ej + 4] != '.') continue;
    if (board[6 * ei + i][6 * ej + 3] != '.') continue;

    board[6 * si + i][6 * sj + 0] = 'z' - f;
    board[6 * ei + i][6 * ej + 5] = '_';
    board[6 * ei + i][6 * ej + 4] = 'z' - f;
    board[6 * ei + i][6 * ej + 3] = 'z' - f;
    break;
  }
}

void drill_left_2(int si, int sj, int ei, int ej) {
  for (int i = 0; i < 5; ++i) {
    if (board[6 * si + i][6 * sj + 0] != '.') continue;
    if (board[6 * si + i][6 * sj + 1] != '.') continue;
    if (board[6 * ei + i][6 * ej + 4] != '.') continue;

    board[6 * si + i][6 * sj + 0] = 'z' - f;
    board[6 * si + i][6 * sj + 1] = 'z' - f;
    board[6 * ei + i][6 * ej + 5] = '_';
    board[6 * ei + i][6 * ej + 4] = 'z' - f;
    break;
  }
}

void drill_down_1(int si, int sj, int ei, int ej) {
  for (int j = 0; j < 5; ++j) {
    if (board[6 * si + 4][6 * sj + j] != '.') continue;
    if (board[6 * ei + 0][6 * ej + j] != '.') continue;
    if (board[6 * ei + 1][6 * ej + j] != '.') continue;

    board[6 * si + 4][6 * sj + j] = 'z' - f;
    board[6 * si + 5][6 * sj + j] = '_';
    board[6 * ei + 0][6 * ej + j] = 'z' - f;
    board[6 * ei + 1][6 * ej + j] = 'z' - f;
    break;
  }
}

void drill_down_2(int si, int sj, int ei, int ej) {
  for (int j = 0; j < 5; ++j) {
    if (board[6 * si + 3][6 * sj + j] != '.') continue;
    if (board[6 * si + 4][6 * sj + j] != '.') continue;
    if (board[6 * ei + 0][6 * ej + j] != '.') continue;

    board[6 * si + 3][6 * sj + j] = 'z' - f;
    board[6 * si + 4][6 * sj + j] = 'z' - f;
    board[6 * si + 5][6 * sj + j] = '_';
    board[6 * ei + 0][6 * ej + j] = 'z' - f;
    break;
  }
}

void drill(int i, int j, int rem) {
  if (rem == 0) return;

  f = (f + 1) % 5;
  if (i % 2 == 0) {
    if (j == M - 1) {
      if (rem == 1) drill_down_1(i, j, i + 1, j);
      else drill_down_2(i, j, i + 1, j);
    }
    else {
      if (rem == 1) drill_right_1(i, j, i, j + 1);
      else drill_right_2(i, j, i, j + 1);
    }
  }
  else {
    if (j == 0) {
      if (rem == 1) drill_down_1(i, j, i + 1, j);
      else drill_down_2(i, j, i + 1, j);
    }
    else {
      if (rem == 1) drill_left_1(i, j, i, j - 1);
      else drill_left_2(i, j, i, j - 1);
    }
  }
}

void fill();
int ok, si, sj, c;

void init() {
  ok = 0;
  c = 'a' - 1;
}

void print() {
  for (int i = 6 * si; i < 6 * si + 5; ++i) {
    for (int j = 6 * sj; j < 6 * sj + 5; ++j) cout << board[i][j];
    cout << '\n';
  }
}

void fill() {
  if (ok) return;
  ++c; ok = 1;
  for (int i = 6 * si; i < 6 * si + 5; ++i) for (int j = 6 * sj; j < 6 * sj + 5; ++j) {
    if (board[i][j] != '.') continue;
    ok = 0;

    for (int k1 = 0; k1 < 4; ++k1) {
      int i1 = i + dx[k1], j1 = j + dy[k1];
      if (i1 < 6 * si || i1 >= 6 * si + 5 || j1 < 6 * sj || j1 >= 6 * sj + 5) continue;
      if (board[i1][j1] != '.') continue;

      for (int k2 = 0; k2 < 4; ++k2) {
        int i2 = i1 + dx[k2], j2 = j1 + dy[k2];
        if (i2 < 6 * si || i2 >= 6 * si + 5 || j2 < 6 * sj || j2 >= 6 * sj + 5) continue;
        if (board[i2][j2] != '.') continue;
        if (i == i2 && j == j2) continue;

        board[i][j] = board[i1][j1] = board[i2][j2] = c;
        fill();
        if (ok) return;
        board[i][j] = board[i1][j1] = board[i2][j2] = '.';
      }

      for (int k2 = 0; k2 < 4; ++k2) {
        int i2 = i + dx[k2], j2 = j + dy[k2];
        if (i2 < 6 * si || i2 >= 6 * si + 5 || j2 < 6 * sj || j2 >= 6 * sj + 5) continue;
        if (board[i2][j2] != '.') continue;
        if (i1 == i2 && j1 == j2) continue;

        board[i][j] = board[i1][j1] = board[i2][j2] = c;
        fill();
        if (ok) return;
        board[i][j] = board[i1][j1] = board[i2][j2] = '.';
      }
    }
  }
  if (ok) return;
  --c;
}

int cnt_blank(int si, int sj) {
  int cnt = 0;
  for (int i = 6 * si; i < 6 * si + 5; ++i) for (int j = 6 * sj; j < 6 * sj + 5; ++j) {
    if (board[i][j] == '.') ++cnt;
  }
  return cnt;
}

void write_to_file() {
  ofstream fout("watering7.in");
  fout << N << ' ' << M << '\n';
  for (int i = 0; i < 6 * N - 1; ++i) {
    for (int j = 0; j < 6 * M - 1; ++j) {
      fout << board[i][j];
    }
    fout << '\n';
  }
  fout.close();
}

void solve() {
  cin >> N >> M;
  for (int i = 0; i < 6 * N - 1; ++i) {
    cin >> board[i];
  }

  for (si = 0; si < N; ++si) {
    if (si & 1) {
      for (sj = M - 1; sj >= 0; --sj) {
        drill(si, sj, cnt_blank(si, sj) % 3);
      }
    }
    else {
      for (sj = 0; sj < M; ++sj) {
        drill(si, sj, cnt_blank(si, sj) % 3);
      }
    }
  }

  for (si = 0; si < N; ++si) for (sj = 0; sj < M; ++sj) {
    cout << "entry = " << si << ' ' << sj << '\n';
    print();
    cout << "====================" << endl;
    init(); fill();

    cout << "si = " << si << ", sj = " << sj << " passed\n";
    print();
    cout << "====================" << endl;

    write_to_file();
  }

  for (int i = 0; i < 6 * N - 1; ++i) cout << board[i] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
