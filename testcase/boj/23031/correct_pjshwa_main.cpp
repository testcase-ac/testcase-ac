#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 15;
const int dx[] = {1, 0, -1, 0}, dy[] = {0, -1, 0, 1};
char board[MAXN + 1][MAXN + 1];
int S[MAXN][MAXN], N;

bool oob(int x, int y) {
  return x < 0 || x >= N || y < 0 || y >= N;
}

void switch_on(int x, int y) {
  for (int cx = x - 1; cx <= x + 1; ++cx) {
    for (int cy = y - 1; cy <= y + 1; ++cy) {
      if (!oob(cx, cy)) S[cx][cy] = 1;
    }
  }
}

vector<tuple<int, int, int>> Z;
bool check_encounter(int px, int py) {
  if (S[px][py]) return false;
  for (auto& [zx, zy, _] : Z) {
    if (px == zx && py == zy) return true;
  }
  return false;
}

bool check_answer() {
  string A; cin >> N >> A;

  for (int i = 0; i < N; ++i) {
    cin >> board[i];
    for (int j = 0; j < N; ++j) {
      if (board[i][j] == 'Z') Z.emplace_back(i, j, 0);
    }
  }

  int px = 0, py = 0, dir = 0;
  for (char c : A) {
    // move player
    if (c == 'F') {
      int nx = px + dx[dir], ny = py + dy[dir];
      if (!oob(nx, ny)) px = nx, py = ny;
    }
    if (c == 'L') dir = (dir + 3) % 4;
    if (c == 'R') dir = (dir + 1) % 4;

    // turn on switch if there is one
    if (board[px][py] == 'S') switch_on(px, py);

    // check encounter first
    if (check_encounter(px, py)) return false;

    // move zombies
    for (auto& [zx, zy, zd] : Z) {
      int nx = zx + dx[zd], ny = zy + dy[zd];
      if (oob(nx, ny)) zd = (zd + 2) % 4;
      else zx = nx, zy = ny;
    }

    // check encounter again
    if (check_encounter(px, py)) return false;
  }

  return true;
}

void solve() {
  if (check_answer()) cout << "Phew...\n";
  else cout << "Aaaaaah!\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
