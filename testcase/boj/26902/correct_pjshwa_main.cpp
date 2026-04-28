#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  string s; cin >> s;
  int n = s.size();
  vector<vector<string>> ans;
  vector<string> cur;

  function<void(int, int)> dfs = [&](int i, int k) {
    if (i == n && k == 4) {
      ans.push_back(cur);
      return;
    }
    if (i == n || k == 4) return;

    for (int j = i; j < i + 3 && j < n; j++) {
      string t = s.substr(i, j - i + 1);
      if (t.size() > 1 && t[0] == '0') continue;
      if (stoi(t) > 255) continue;

      cur.push_back(t);
      dfs(j + 1, k + 1);
      cur.pop_back();
    }
  };
  dfs(0, 0);

  cout << ans.size() << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
