#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int vis[100'001];
vector<int> graph[100'001];
int main() {
  fast_io();

  int n, k;
  cin >> n >> k;

  unordered_map<string, int> sidx;
  string word;
  for (int i = 1; i <= n; i++) {
    cin >> word;
    sidx[word] = i;
  }

  string nw;
  for (auto[el, idx] : sidx) {
    for (int i = 0; i < k; i++) {
      nw = el;
      nw[i] = nw[i] == '0' ? '1' : '0';

      if (sidx.count(nw) && idx < sidx[nw]) {
        graph[idx].push_back(sidx[nw]);
        graph[sidx[nw]].push_back(idx);
      }
    }
  }

  int m, t;
  cin >> m;

  while (m--) {
    memset(vis, 0, sizeof(vis));
    cin >> t;

    queue<pair<int, int>> q;
    q.push({1, -1});

    int vtx, pt;
    while (!q.empty()) {
      tie(vtx, pt) = q.front();
      q.pop();

      if (vis[vtx]) continue;
      vis[vtx] = pt;

      if (vtx == t) break;

      for (auto dst : graph[vtx]) {
        if (!vis[dst]) q.push({dst, vtx});
      }
    }

    if (vtx == t) {
      vector<int> ans;
      while (vtx != -1) {
        ans.push_back(vtx);
        vtx = vis[vtx];
      }

      int sz = ans.size();
      for (int i = sz - 1; i >= 0; i--) cout << ans[i] << ' ';
    }
    else cout << -1;
    cout << '\n';
  }
}
