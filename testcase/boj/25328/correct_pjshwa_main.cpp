#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

string S[3];
map<string, int> t;
int k;
string cur = "";

void dfs(int si, int i) {
  if (cur.size() == k) {
    t[cur]++;
    return;
  }

  for (int l = i; l < S[si].size(); l++) {
    cur += S[si][l];
    dfs(si, l + 1);
    cur.pop_back();
  }
}

void solve() {
  for (int i = 0; i < 3; i++) cin >> S[i];
  cin >> k;

  for (int i = 0; i < 3; i++) dfs(i, 0);

  vector<string> ans;
  for (auto& [k, v] : t) {
    if (v >= 2) ans.push_back(k);
  }

  if (ans.empty()) cout << "-1\n";
  else {
    for (auto& s : ans) cout << s << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
