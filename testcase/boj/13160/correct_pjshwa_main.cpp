#include <bits/stdc++.h>
#define pii pair<int, int>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  int n, s, e;
  vector<pii> points, pse;
  cin >> n;

  for (int i = 0; i < n; i++) {
    cin >> s >> e;
    points.push_back({s, e});
    pse.push_back({s, 0});
    pse.push_back({e, 1});
  }
  sort(pse.begin(), pse.end());

  int mv = -1, mi = -1, cnt = 0;
  for (auto [i, t] : pse) {
    if (t == 0) cnt++;
    if (mv < cnt) {
      mv = cnt;
      mi = i;
    }
    if (t == 1) cnt--;
  }

  cout << mv << '\n';
  for (int i = 0; i < n; i++) {
    auto [s, e] = points[i];
    if (s <= mi && mi <= e) cout << i + 1 << ' ';
  }
}
