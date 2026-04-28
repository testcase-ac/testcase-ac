#include <iostream>
#include <queue>
#include <tuple>
#define pii pair<int, int>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

char maze[51][50];
bool pvis[51][50];
int main() {
  fast_io();

  int r, c;
  cin >> c >> r;
  for (int i = 0; i < r; i++) cin >> maze[i];

  queue<pii> player_q;
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      if (maze[i][j] == 'P') {
        maze[i][j] = '.';
        pvis[i][j] = true;
        player_q.push({i, j});
      }
    }
  }

  int px, py, psz, ans = 0;
  while (!player_q.empty()) {
    psz = player_q.size();

    while (psz--) {
      tie(px, py) = player_q.front();
      player_q.pop();

      if (maze[px][py] == 'G') ans++;

      // Don't explore further if she "senses a draft"
      if (
        maze[px - 1][py] == 'T' ||
        maze[px + 1][py] == 'T' ||
        maze[px][py - 1] == 'T' ||
        maze[px][py + 1] == 'T'
      ) continue;

      if (px > 0 && (maze[px - 1][py] == '.' || maze[px - 1][py] == 'G') && !pvis[px - 1][py]) {
        pvis[px - 1][py] = true;
        player_q.push({px - 1, py});
      }
      if (px < r - 1 && (maze[px + 1][py] == '.' || maze[px + 1][py] == 'G') && !pvis[px + 1][py]) {
        pvis[px + 1][py] = true;
        player_q.push({px + 1, py});
      }
      if (py > 0 && (maze[px][py - 1] == '.' || maze[px][py - 1] == 'G') && !pvis[px][py - 1]) {
        pvis[px][py - 1] = true;
        player_q.push({px, py - 1});
      }
      if (py < c - 1 && (maze[px][py + 1] == '.' || maze[px][py + 1] == 'G') && !pvis[px][py + 1]) {
        pvis[px][py + 1] = true;
        player_q.push({px, py + 1});
      }
    }
  }

  cout << ans << '\n';
}
