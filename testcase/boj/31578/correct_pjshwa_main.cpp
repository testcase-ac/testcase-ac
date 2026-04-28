#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 200, MAXL = 20;
string S[MAXN];
vector<int> adj[MAXN];
int color[MAXN];

void dfs(int v, int c) {
  color[v] = c;
  for (int u : adj[v]) {
    if (color[u] == -1) dfs(u, c ^ 1);
    else if (color[u] == c) {
      cout << "No\n";
      exit(0);
    }
  }
}

void solve() {
  int N, K; cin >> N >> K;
  for (int i = 0; i < N; ++i) cin >> S[i];

  for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) {
    if (i == j) continue;

    int tot = 0, iz = S[i].size(), jz = S[j].size();
    for (int si = 0; si < iz; ++si) for (int sj = 0; sj < jz; ++sj) {
      int cur = 0, ci = si, cj = sj;
      while (ci < iz && cj < jz && S[i][ci] == S[j][cj]) {
        ++cur; ++ci, ++cj;
      }
      tot = max(tot, cur);
    }
    // cout << "i: " << i << " j: " << j << " tot: " << tot << '\n';

    if (tot >= K) {
      adj[i].push_back(j);
      adj[j].push_back(i);
    }
  }

  memset(color, -1, sizeof(color));
  for (int i = 0; i < N; ++i) {
    if (color[i] != -1) continue;
    dfs(i, 0);
  }

  cout << "Yes\n";

  vector<int> ans; set<int> ans_u;
  for (int i = 0; i < N; ++i) {
    int c = color[i] + 1;
    ans.push_back(c);
    ans_u.insert(c);
  }
  if (ans_u.size() == 1) ans[0] = 2;
  for (int i = 0; i < N; ++i) cout << ans[i] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
