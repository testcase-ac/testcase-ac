#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

set<int> G[26];
int deg[26], d[26], c[26];

void solve() {
  int N;
  cin >> N;
  vector<string> words(N);
  for (int i = 0; i < N; i++) {
    cin >> words[i];
    int s = words[i][0] - 'a', e = words[i].back() - 'a';
    G[e].insert(s);
  }

  for (int i = 0; i < 26; i++) {
    for (int s : G[i]) deg[s]++;
  }

  memset(d, -1, sizeof(d));

  queue<pii> q;
  for (int i = 0; i < 26; i++) {
    if (deg[i] == 0) {
      d[i] = 0;
      q.push({i, 0});
    }
  }

  while (!q.empty()) {
    auto [v, k] = q.front(); q.pop();

    for (int u : G[v]) {
      if (d[u] != -1) continue;

      if (k) {
        deg[u]--;
        if (deg[u] == 0) {
          d[u] = 0;
          q.push({u, 0});
        }
      }
      else {
        d[u] = 1;
        q.push({u, 1});
      }
    }
  }

  vector<string> ans;
  for (int i = 0; i < N; i++) {
    int e = words[i].back() - 'a';
    if (d[e] == 0) ans.push_back(words[i]);
  }

  sort(ans.begin(), ans.end());
  cout << ans.size() << '\n';
  for (string s : ans) cout << s << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
