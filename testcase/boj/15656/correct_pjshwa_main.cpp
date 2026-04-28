#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int a[7];
int n, m;
vector<int> cur;
vector<string> ans;

void dfs(int d) {
  if (d == m) {
    string res = "";
    for (auto& e : cur) res += to_string(e), res += " ";
    if (ans.empty() || ans.back() != res) ans.push_back(res);
    return;
  }
  for (int i = 0; i < n; i++) {
    cur.push_back(a[i]);
    dfs(d + 1);
    cur.pop_back();
  }
}

void solve() {
  cin >> n >> m;
  for (int i = 0; i < n; i++) cin >> a[i];
  sort(a, a + n);
  dfs(0);
  for (auto s : ans) cout << s << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
