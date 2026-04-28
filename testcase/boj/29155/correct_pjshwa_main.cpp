#include <bits/stdc++.h> 
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int problems_cnt; cin >> problems_cnt;

  int need_by_level[5];
  for (int i = 0; i < 5; ++i) cin >> need_by_level[i];

  vector<int> problems_by_level[5];
  for (int i = 0; i < problems_cnt; ++i) {
    int level, time; cin >> level >> time;
    problems_by_level[level - 1].push_back(time);
  }

  int ans = 0;
  for (int i = 0; i < 5; ++i) {
    if (need_by_level[i] == 0) continue;
    if (i > 0) ans += 60;

    sort(problems_by_level[i].begin(), problems_by_level[i].end());

    int cur = problems_by_level[i][0];
    for (int j = 1; j < need_by_level[i]; ++j) {
      cur += problems_by_level[i][j];
      cur += (problems_by_level[i][j] - problems_by_level[i][j - 1]);
    }
    ans += cur;
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
