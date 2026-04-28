#include <bits/stdc++.h>
#define pii pair<int, int>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

vector<int> egraph[10001];
vector<int> rgraph[10001];

pii times[10001];
int tick = 0;
int cc = 0;
int vis[10001];

void clock_dfs(int v) {
  vis[v] = 1;
  tick++;

  for (auto dst: rgraph[v]) {
    if (!vis[dst]) clock_dfs(dst);
  }
  times[v] = {++tick, v};
}

void dfs(int v, int cc) {
  vis[v] = cc;
  for (auto dst: egraph[v]) {
    if (!vis[dst]) dfs(dst, cc);
  }
}

int main() {
  fast_io();

  int v, e, a, b;
  cin >> v >> e;

  while (e--) {
    cin >> a >> b;
    egraph[a].push_back(b);
    rgraph[b].push_back(a);
  }

  for (int i = 1; i <= v; i++) {
    if (!vis[i]) clock_dfs(i);
  }

  memset(vis, 0, sizeof(vis));
  sort(times + 1, times + v + 1);

  for (int i = v; i >= 1; i--) {
    int vtx = times[i].second;
    if (!vis[vtx]) dfs(vtx, ++cc);
  }

  cout << cc << '\n';
  set<int> ccs;
  vector<int> ccv;

  for (int i = 1; i <= v; i++) {
    if (!ccs.count(vis[i])) {
      ccv.push_back(vis[i]);
      ccs.insert(vis[i]);
    }
  }

  map<int, vector<int>> ccmv;
  for (int i = 1; i <= v; i++) {
    auto found = ccmv.find(vis[i]);
    if (found != ccmv.end()) found->second.push_back(i);
    else {
      vector<int> vt;
      vt.push_back(i);
      ccmv.insert({vis[i], vt});
    }
  }

  for (auto el : ccv) {
    for (auto elv : ccmv[el]) cout << elv << ' ';
    cout << "-1\n";
  }
}
