#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int INF = 1e9 + 7;

int main() {
  fast_io();

  int a, b, c, d, x;
  cin >> a >> b >> c >> d;

  vector<tuple<int, int, int>> ab;
  vector<int> t;

  for (int i = 0; i < a; i++) {
    cin >> x;
    t.push_back(x);
  }

  for (int i = 0; i < b; i++) {
    cin >> x;
    for (int e : t) ab.push_back(make_tuple(e + x, e, x));
  }
  sort(ab.begin(), ab.end());
  t.clear();

  for (int i = 0; i < c; i++) {
    cin >> x;
    t.push_back(x);
  }

  for (int i = 0; i < d; i++) {
    cin >> x;
    for (int e : t) {
      auto it = lower_bound(ab.begin(), ab.end(), make_tuple(-(e + x), -INF, -INF));
      if (get<0>(*it) == -(e + x)) {
        cout << get<1>(*it) << ' ' << get<2>(*it) << ' ' << e << ' ' << x;
        return 0;
      }
    }
  }
}
