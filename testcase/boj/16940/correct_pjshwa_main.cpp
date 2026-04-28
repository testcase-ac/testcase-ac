#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
int level[MAX], parent[MAX], ccount[MAX];
bool vis[MAX];
vector<int> g[MAX];

void dfs(int v, int lv) {
  vis[v] = true;
  level[v] = lv;
  for (int d : g[v]) {
    if (!vis[d]) {
      parent[d] = v;
      ccount[v]++;
      dfs(d, lv + 1);
    }
  }
}

int main() {
  fast_io();

  int v, a, b;
  cin >> v;

  for (int i = 0; i < v - 1; i++) {
    cin >> a >> b;
    g[a - 1].push_back(b - 1);
    g[b - 1].push_back(a - 1);
  }

  vector<int> o;
  o.resize(v);
  for (int i = 0; i < v; i++) cin >> o[i], o[i]--;
  dfs(0, 0);
  parent[0] = -1;

  int idx = 0;
  vector<int> parents;
  parents.push_back(-1);

  while (idx < v) {
    vector<int> nparents;
    for (int v : parents) {
      int c = v == -1 ? 1 : ccount[v];
      while (c--) {
        int co = o[idx++];
        if (parent[co] != v) return cout << 0, 0;
        nparents.push_back(co);
      }
    }
    parents = nparents;
  }

  cout << 1;
}
