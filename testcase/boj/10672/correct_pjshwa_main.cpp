#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  int n;
  cin >> n;
  vector<tuple<int, int, int>> a(n);
  set<int> s;

  for (int i = 0; i < n; i++) {
    int x, y, r;
    cin >> x >> y >> r;
    x = x * -r;
    a[i] = make_tuple(y, x - r, x);
    s.insert(x - r - 1);
    s.insert(x - r);
    s.insert(x - r + 1);
    s.insert(x - 1);
    s.insert(x);
    s.insert(x + 1);
  }
  sort(a.begin(), a.end());

  int ans = 0;
  for (auto [y, si, ei] : a) {
    auto li = s.lower_bound(si), ui = s.lower_bound(ei);
    if (li != ui) {
      ans++;
      s.erase(li, ui);
    }
  }

  cout << ans << '\n';
}
