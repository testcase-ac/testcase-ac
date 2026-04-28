#include <bits/stdc++.h>
#define pii pair<int, int>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

bool vis[1 << 15];
int main() {
  fast_io();

  string s, t;
  cin >> s >> t;

  // binary string to integer
  int si = stoi(s, 0, 2);
  int ti = stoi(t, 0, 2);

  // Vertex, depth
  queue<pii> q;
  q.push({si, 0});

  int vtx, dpt;
  while (!q.empty()) {
    tie(vtx, dpt) = q.front();
    q.pop();

    if (vtx == ti) {
      cout << dpt;
      return 0;
    }

    if (vis[vtx]) continue;
    vis[vtx] = true;

    if (!vis[vtx + 1]) q.push({vtx + 1, dpt + 1});
    if (vtx > 0 && !vis[vtx - 1]) q.push({vtx - 1, dpt + 1});

    for (int bit = 0; bit <= 10; bit++) {
      int dst = 1 << bit;
      if (vtx < 2 * dst) break;

      if (vtx & dst) {
        if (!vis[vtx - dst]) q.push({vtx - dst, dpt + 1});
      }
      else {
        if (!vis[vtx + dst]) q.push({vtx + dst, dpt + 1});
      }
    }
  }

}
