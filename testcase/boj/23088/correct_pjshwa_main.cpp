#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  int n;
  cin >> n;
  vector<tuple<int, int, int, int>> p(n);

  for (int i = 0; i < n; i++) {
    int x, y, z;
    cin >> x >> y >> z;
    p[i] = make_tuple(x, y, z, i + 1);
  }
  sort(p.begin(), p.end());

  int ctime = 0, ci = 0;
  priority_queue<tuple<int, int, int>> pq;
  for (int i = 0; i < n; i++) {
    if (pq.empty()) {
      ctime = get<0>(p[ci]);
      while (ci < n && get<0>(p[ci]) <= ctime) {
        auto [x, y, z, si] = p[ci++];
        pq.push({y - x, -z, -si});
      }
    }

    auto [_, z, si] = pq.top();
    cout << -si << ' ';
    ctime -= z;
    pq.pop();

    while (ci < n && get<0>(p[ci]) <= ctime) {
      auto [x, y, z, si] = p[ci++];
      pq.push({y - x, -z, -si});
    }
  }
}
