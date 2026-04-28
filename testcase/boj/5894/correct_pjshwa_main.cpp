#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int n, ans;
pii a[10];
bool vis[10];
vector<pair<pii, char>> current;

bool movable(pii src, pii dst, char cd) {
  auto [sx, sy] = src;
  auto [dx, dy] = dst;
  if (cd == 'N') return sy == dy || (sx == dx && sy > dy);
  if (cd == 'S') return sy == dy || (sx == dx && sy < dy);
  if (cd == 'E') return sx == dx || (sy == dy && sx > dx);
  if (cd == 'W') return sx == dx || (sy == dy && sx < dx);
  return sx == dx || sy == dy;
}

char mdir(pii src, pii dst) {
  auto [sx, sy] = src;
  auto [dx, dy] = dst;
  if (sy == dy) {
    if (dx > sx) return 'E';
    else return 'W';
  }
  else {
    if (dy > sy) return 'N';
    else return 'S';
  }
}

void dfs() {
  auto [p, c] = current.back();

  if (current.size() == n + 1) {
    if (movable(p, {0, 0}, c)) ans++;
    return;
  }

  for (int i = 0; i < n; i++) {
    if (vis[i]) continue;
    if (movable(p, a[i], c)) {
      vis[i] = true;
      current.push_back({a[i], mdir(p, a[i])});
      dfs();
      vis[i] = false;
      current.pop_back();
    }
  }
}

int main() {
  fast_io();

  cin >> n;
  for (int i = 0; i < n; i++) cin >> a[i].first >> a[i].second;
  current.push_back({{0, 0}, 'X'});
  dfs();
  cout << ans << '\n';
}
