#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  int n;
  cin >> n;
  vector<pair<int, int>> segments;
  segments.push_back(make_pair(0, 0));
  for (int i = 0; i < n; i++) {
    int x, y;
    cin >> x >> y;
    segments.push_back(make_pair(x, y));
  }
  segments.push_back(make_pair(1e9, 1e9));
  sort(segments.begin(), segments.end());

  int min_diff = 1e9, min_idx = -1;
  for (int i = 1; i <= n; i++) {
    auto [ps, pe] = segments[i - 1];
    auto [cs, ce] = segments[i];
    auto [ns, ne] = segments[i + 1];

    cs = max(cs, pe);
    ce = min(ce, ns);
    if (min_diff > ce - cs) {
      min_diff = ce - cs;
      min_idx = i;
    }
  }

  int s = 0, cs = -2e9, ce = -2e9;
  for (int i = 1; i <= n; i++) {
    if (i == min_idx) continue;

    auto [as, ae] = segments[i];
    if (ce < as) {
      s += (ce - cs);
      cs = as;
      ce = ae;
    }
    else ce = max(ae, ce);
  }
  cout << s + ce - cs;
}
