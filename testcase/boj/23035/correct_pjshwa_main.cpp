#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  int n, m, t;
  vector<pair<int, int>> cats;
  cin >> n >> m >> t;
  while (t--) {
    int r, c;
    cin >> r >> c;
    if (r <= n && c <= m) cats.push_back({r, c});
  }
  sort(cats.begin(), cats.end());

  vector<int> lis_vector;
  lis_vector.push_back(-(1e9 + 1));

  for (auto [x, next] : cats) {
    if (next < lis_vector[0]) lis_vector[0] = next;
    else if (next >= lis_vector.back()) lis_vector.push_back(next);
    else {
      auto it = upper_bound(lis_vector.begin(), lis_vector.end(), next);
      *it = next;
    }
  }
  cout << lis_vector.size() - 1 << '\n';
}
