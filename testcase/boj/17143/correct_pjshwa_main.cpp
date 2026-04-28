#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

struct Shark;
const int MAX = 100;
int n, m;
int board[MAX + 1][MAX + 1];
vector<Shark> sharks;

struct Shark {
  int id, r, c, s, size;
  bool h, dir, dead = false;

  void move() {
    if (h) {
      int len = s % (2 * m - 2);
      bool flip = !dir;

      if (!dir) dir = true, c = m + 1 - c;

      if (c + len <= m) c += len;
      else if (c + len <= 2 * m - 1) dir = !dir, c = m - (c + len - m);
      else c -= 2 * m - 2 - len;

      if (flip) dir = !dir, c = m + 1 - c;
    }
    else {
      int len = s % (2 * n - 2);
      bool flip = !dir;

      if (!dir) dir = true, r = n + 1 - r;

      if (r + len <= n) r += len;
      else if (r + len <= 2 * n - 1) dir = !dir, r = n - (r + len - n);
      else r -= 2 * n - 2 - len;

      if (flip) dir = !dir, r = n + 1 - r;
    }
  }
};

void print_board() {
  for (int j = 1; j <= m; j++) cout << "--";
  cout << endl;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      cout << board[i][j] << ' ';
    }
    cout << '\n';
  }
  for (int j = 1; j <= m; j++) cout << "--";
  cout << endl;
}

void solve() {
  int u;
  cin >> n >> m >> u;

  // Push back dummy
  sharks.push_back({0, 0, 0, 0, 0});

  for (int i = 1; i <= u; i++) {
    int r, c, s, d, z;
    cin >> r >> c >> s >> d >> z;

    Shark shark = {i, r, c, s, z};
    if (d == 1) shark.h = false, shark.dir = false;
    if (d == 2) shark.h = false, shark.dir = true;
    if (d == 3) shark.h = true, shark.dir = true;
    if (d == 4) shark.h = true, shark.dir = false;
    sharks.push_back(shark);
    board[r][c] = i;
  }

  int ans = 0;
  for (int j = 1; j <= m; j++) {
    for (int i = 1; i <= n; i++) {
      if (board[i][j]) {
        sharks[board[i][j]].dead = true;
        ans += sharks[board[i][j]].size;
        board[i][j] = 0;
        break;
      }
    }

    for (int i = 1; i <= u; i++) {
      if (sharks[i].dead) continue;

      board[sharks[i].r][sharks[i].c] = 0;
      sharks[i].move();
    }

    for (int i = 1; i <= u; i++) {
      if (sharks[i].dead) continue;

      int r = sharks[i].r, c = sharks[i].c;
      if (board[r][c]) {
        if (sharks[board[r][c]].size > sharks[i].size) sharks[i].dead = true;
        else {
          sharks[board[r][c]].dead = true;
          board[r][c] = sharks[i].id;
        }
      }
      else board[r][c] = sharks[i].id;
    }

    // print_board();
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
