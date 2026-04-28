#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

bool is_equal(double a, double b) {
  return abs(a - b) < 1e-9;
}

void solve() {
  int N, M; cin >> N >> M;

  set<tuple<int, int, int>> s;
  for (int i1 = 0; i1 <= N; ++i1) for (int i2 = 0; i2 <= N; ++i2) for (int i3 = 0; i3 <= N; ++i3) 
  for (int j1 = 0; j1 <= M; ++j1) for (int j2 = 0; j2 <= M; ++j2) for (int j3 = 0; j3 <= M; ++j3) {
    int d1 = (i1 - i2) * (i1 - i2) + (j1 - j2) * (j1 - j2);
    int d2 = (i2 - i3) * (i2 - i3) + (j2 - j3) * (j2 - j3);
    int d3 = (i3 - i1) * (i3 - i1) + (j3 - j1) * (j3 - j1);

    // skip if not triangle
    if (d1 == 0 || d2 == 0 || d3 == 0) continue;
    double q1 = sqrt(d1), q2 = sqrt(d2), q3 = sqrt(d3);
    if (is_equal(q1, q2 + q3) || is_equal(q2, q1 + q3) || is_equal(q3, q1 + q2)) continue;

    vector<int> v = {d1, d2, d3};
    sort(v.begin(), v.end());
    s.emplace(v[0], v[1], v[2]);
  }

  cout << s.size() << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
