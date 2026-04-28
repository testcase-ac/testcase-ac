#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int vis[1'000'000];
char smap[1'000'000];
void bfs(int n) {
  queue<int> q;
  q.push(1 % n);
  vis[1 % n] = -1;
  smap[1 % n] = '1';

  while (1) {
    int r = q.front();
    q.pop();

    if (r == 0) {
      stack<int> traj;
      while (r != -1) {
        traj.push(r);
        r = vis[r];
      }
      while (!traj.empty()) {
        cout << smap[traj.top()];
        traj.pop();
      }
      cout << '\n';
      return;
    }

    int az = (r * 10 + 0) % n, ao = (r * 10 + 1) % n;
    if (!vis[az]) {
      vis[az] = r;
      smap[az] = '0';
      q.push(az);
    }
    if (!vis[ao]) {
      vis[ao] = r;
      smap[ao] = '1';
      q.push(ao);
    }
  }
}

int n;
void solve() {
  memset(vis, 0, sizeof(vis));
  bfs(n);
}

int main() {
  fast_io();

  while (1) {
    cin >> n;
    if (n == 0) break;
    solve();
  }
}
