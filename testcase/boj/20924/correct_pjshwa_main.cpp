#include <bits/stdc++.h>
#define pii pair<int, int>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

vector<pii> graph[200001];
bool vis[200001];
int gn = -1;
int gl = -1;
int dfs(int node, int ml) {
  vis[node] = true;

  int b, d, mv = ml;
  int cnt = 0;
  for (pii p : graph[node]) {
    tie(b, d) = p;
    if (!vis[b]) cnt++;
  }
  if (gn == -1 && cnt != 1) {
    gn = node;
    gl = ml;
  }

  for (pii p : graph[node]) {
    tie(b, d) = p;
    if (!vis[b]) mv = max(mv, dfs(b, ml + d));
  }
  return mv;
}

int main() {
  fast_io();

  int n, r, a, b, d;
  cin >> n >> r;

  for (int i = 0; i < n - 1; i++) {
    cin >> a >> b >> d;
    graph[a].push_back({b, d});
    graph[b].push_back({a, d});
  }

  int mv = dfs(r, 0);
  cout << gl << ' ' << mv - gl << '\n';
}
