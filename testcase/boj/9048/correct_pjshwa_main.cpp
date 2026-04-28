#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

vector<int> os[31];

int main() {
  fast_io();

  int t;
  cin >> t;
  while (t--) {
    int f, r, n;
    cin >> f >> r >> n;

    for (int i = 1; i <= f; i++) os[i].clear();

    for (int i = 0; i < n; i++) {
      int a, b;
      cin >> a >> b;
      os[a].push_back(b);
    }

    int ans = r + 1 + 2 * f;
    for (int i = 1; i <= f; i++) {
      int sz = os[i].size();
      if (!sz) continue;
      sort(os[i].begin(), os[i].end());

      int mv = min(os[i][sz - 1], r + 1 - os[i][0]);

      for (int z = 0; z < sz - 1; z++) mv = min(mv, os[i][z] + r + 1 - os[i][z + 1]);
      ans += 2 * mv;
    }

    cout << ans << '\n';
  }

}
