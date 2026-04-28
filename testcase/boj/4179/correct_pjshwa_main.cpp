#include <iostream>
#include <queue>
#include <tuple>
#define pii pair<int, int>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

char maze[1001][1000];
bool jvis[1001][1000];
int main() {
  fast_io();

  int r, c;
  cin >> r >> c;
  for (int i = 0; i < r; i++) cin >> maze[i];

  queue<pii> jq;
  queue<pii> fq;

  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      if (maze[i][j] == 'F') fq.push({i, j});
    }
  }

  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      if (maze[i][j] == 'J') {
        maze[i][j] = '.';
        jvis[i][j] = true;
        jq.push({i, j});
      }
    }
  }

  int fx, fy, jx, jy, fsz, jsz, tick = 0;
  bool escaped = false;
  while (!jq.empty()) {
    fsz = fq.size();
    jsz = jq.size();

    while (fsz--) {
      tie(fx, fy) = fq.front();
      fq.pop();

      if (fx > 0 && maze[fx - 1][fy] == '.') {
        maze[fx - 1][fy] = 'F';
        fq.push({fx - 1, fy});
      }
      if (fx < r - 1 && maze[fx + 1][fy] == '.') {
        maze[fx + 1][fy] = 'F';
        fq.push({fx + 1, fy});
      }
      if (fy > 0 && maze[fx][fy - 1] == '.') {
        maze[fx][fy - 1] = 'F';
        fq.push({fx, fy - 1});
      }
      if (fy < c - 1 && maze[fx][fy + 1] == '.') {
        maze[fx][fy + 1] = 'F';
        fq.push({fx, fy + 1});
      }
    }

    while (jsz--) {
      tie(jx, jy) = jq.front();
      jq.pop();

      if (jx == 0 || jx == r - 1 || jy == 0 || jy == c - 1) {
        escaped = true;
        break;
      }
      if (jx > 0 && maze[jx - 1][jy] == '.' && !jvis[jx - 1][jy]) {
        jvis[jx - 1][jy] = true;
        jq.push({jx - 1, jy});
      }
      if (jx < r - 1 && maze[jx + 1][jy] == '.' && !jvis[jx + 1][jy]) {
        jvis[jx + 1][jy] = true;
        jq.push({jx + 1, jy});
      }
      if (jy > 0 && maze[jx][jy - 1] == '.' && !jvis[jx][jy - 1]) {
        jvis[jx][jy - 1] = true;
        jq.push({jx, jy - 1});
      }
      if (jy < c - 1 && maze[jx][jy + 1] == '.' && !jvis[jx][jy + 1]) {
        jvis[jx][jy + 1] = true;
        jq.push({jx, jy + 1});
      }
    }

    if (escaped) break;
    tick++;
  }

  if (escaped) cout << tick + 1;
  else cout << "IMPOSSIBLE";
  cout << '\n';

  return 0;
}
