#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

set<string> adj[31];
vector<vector<string>> pre;

bool starts_with(vector<string>& vs, vector<string>& candidate) {
  if (vs.size() < candidate.size()) return false;
  for (int i = 0; i < candidate.size(); ++i) {
    if (vs[i] != candidate[i]) return false;
  }
  return true;
}

void solve() {
  int n, k;
  cin >> n >> k;

  int madj = 0;
  pre.resize(n);
  for (int i = 0; i < n; i++) {
    string s;
    vector<string> pb;
    cin >> s >> s >> s >> s;

    int x = 0;
    while (1) {
      cin >> s;
      if (s == "cow.") break;
      adj[x].insert(s);
      pb.push_back(s);
      x++;
    }
    madj = max(madj, x);
    pre[i] = pb;
  }

  vector<string> ans;
  for (int i = 0; i < madj; i++) {
    int asize = 1;
    for (int j = i + 1; j < madj; j++) asize *= max((int)adj[j].size(), 1);

    for (auto e : adj[i]) {
      int csize = asize;
      ans.push_back(e);

      for (auto& vs : pre) {
        if (!starts_with(vs, ans)) continue;

        int rem = 1;
        for (int k = vs.size(); k < madj; k++) rem *= max((int)adj[k].size(), 1);
        csize -= rem;
      }
      if (k <= csize) break;
      k -= csize;
      ans.pop_back();
    }
  }

  for (auto e : ans) cout << e << " ";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
