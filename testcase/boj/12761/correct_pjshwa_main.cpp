#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
bool vis[MAX + 1];
int a, b, s, e;

void bfs() {
  queue<pii> q;
  q.push({s, 0});
  vis[s] = true;

  while (!q.empty()) {
    auto [x, y] = q.front();
    q.pop();

    if (x == e) return cout << y << '\n', void();

    if (x + 1 <= MAX && !vis[x + 1]) vis[x + 1] = true, q.push({x + 1, y + 1});
    if (x - 1 >= 0 && !vis[x - 1]) vis[x - 1] = true, q.push({x - 1, y + 1});
    if (x + a <= MAX && !vis[x + a]) vis[x + a] = true, q.push({x + a, y + 1});
    if (x - a >= 0 && !vis[x - a]) vis[x - a] = true, q.push({x - a, y + 1});
    if (x + b <= MAX && !vis[x + b]) vis[x + b] = true, q.push({x + b, y + 1});
    if (x - b >= 0 && !vis[x - b]) vis[x - b] = true, q.push({x - b, y + 1});
    if (x * a <= MAX && !vis[x * a]) vis[x * a] = true, q.push({x * a, y + 1});
    if (x * b <= MAX && !vis[x * b]) vis[x * b] = true, q.push({x * b, y + 1});
  }
}

int main() {
  fast_io();

  cin >> a >> b >> s >> e;
  bfs();
}
