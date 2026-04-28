#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int levels[2500];

void drain(int x, int l) {
  levels[x] = max(levels[x], l);
}

int main() {
  fast_io();

  int n, a, b, c, d, q;
  vector<pair<pair<int, int>, int>> h;

  cin >> n;
  a = -1, b = -1;
  while (n--) {
    cin >> c >> d;
    if (b == d) h.push_back({{a, c}, b});
    a = c, b = d;
  }
  n = h.size();

  cin >> q;
  while (q--) {
    cin >> a >> b >> c >> d;
    int x = 0;
    while (h[x].first != make_pair(a, c)) x++;

    drain(x, b);
    for (int i = x - 1; i >= 0; i--) {
      b = min(b, h[i].second);
      drain(i, b);
    }

    for (int i = x + 1; i < n; i++) {
      d = min(d, h[i].second);
      drain(i, d);
    }
  }

  int ans = 0;
  for (int i = 0; i < n; i++) {
    auto p = h[i];
    tie(a, c) = p.first;
    ans += (c - a) * (p.second - levels[i]);
  }
  cout << ans;
}
