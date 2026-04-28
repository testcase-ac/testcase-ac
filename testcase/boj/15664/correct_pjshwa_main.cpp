#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int a[8];
int n, m;
vector<int> cur;
vector<vector<int>> ans;

void dfs(int d, int j) {
  if (d == m) {
    ans.push_back(cur);
    return;
  }
  for (int i = j; i < n; i++) {
    if (!cur.empty() && cur.back() > a[i]) continue;
    cur.push_back(a[i]);
    dfs(d + 1, i + 1);
    cur.pop_back();
  }
}

void solve() {
  cin >> n >> m;
  for (int i = 0; i < n; i++) cin >> a[i];
  sort(a, a + n);
  dfs(0, 0);
  sort(ans.begin(), ans.end(), [] (const vector<int>& a, const vector<int>& b) {
    int n = a.size();
    for (int i = 0; i < n; i++) {
      if (a[i] < b[i]) return true;
      if (a[i] > b[i]) return false;
    }
    return false;
  });
  ans.erase(unique(ans.begin(), ans.end()), ans.end());
  for (auto& e : ans) {
    for (auto& v : e) cout << v << " ";
    cout << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
