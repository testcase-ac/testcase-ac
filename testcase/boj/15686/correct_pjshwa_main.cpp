#include <bits/stdc++.h>
#define pii pair<int, int>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int manhattan_dist(pii p1, pii p2) {
  return abs(p1.first - p2.first) + abs(p1.second - p2.second);
}

int n, m, mv = 1e9;
vector<pii> current, houses, chicken_shops;

void dfs(int cpos) {
  if (current.size() == m) {
    int res = 0;
    for (pii h : houses) {
      int chicken_dist = 1e9;
      for (pii c : current) chicken_dist = min(chicken_dist, manhattan_dist(h, c));
      res += chicken_dist;
    }
    mv = min(res, mv);
    return;
  }
  if (cpos == chicken_shops.size()) return;

  current.push_back(chicken_shops[cpos]);
  dfs(cpos + 1);
  current.pop_back();
  dfs(cpos + 1);
}

int main() {
  fast_io();

  cin >> n >> m;

  int s;
  for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {
    cin >> s;
    if (s == 1) houses.push_back({i, j});
    if (s == 2) chicken_shops.push_back({i, j});
  }

  dfs(0);
  cout << mv;
}
