#include <bits/stdc++.h>
#define pii pair<int, int>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  int n, m, t, k;
  cin >> n >> m >> t >> k;

  vector<pii> points;
  points.resize(t);
  for (int i = 0; i < t; i++) cin >> points[i].first >> points[i].second;

  int mv = -1, mx, my;
  for (pii p1 : points) for (pii p2 : points) {
    if (p2.second < p1.second || p2.first < p1.first) continue;
    if (p2.first > p1.first + k || p2.second > p1.second + k) continue;
    int ymin = max(0, p2.second - k), xmax = min(n, p1.first + k);
    int xmin = xmax - k, ymax = ymin + k;

    int cnt = 0;
    for (pii pt : points) if (xmin <= pt.first && xmax >= pt.first && ymin <= pt.second && ymax >= pt.second) cnt++;
    if (mv < cnt) {
      mv = cnt;
      mx = xmin;
      my = ymax;
    }
  }

  cout << mx << ' ' << my << '\n' << mv;
}
