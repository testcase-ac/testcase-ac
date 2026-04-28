#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1000, INF = 0x3f3f3f3f;
vector<int> adj[MAX + 1];
int indegree[MAX + 1], B[MAX][MAX];

void compress(vector<int>& v) {
  sort(v.begin(), v.end());
  v.erase(unique(v.begin(), v.end()), v.end());
}

void solve() {
  int N, H, W; cin >> N >> W >> H;
  for (int i = 0; i < H; i++) for (int j = 0; j < W; j++) cin >> B[i][j];

  for (int t = 1; t <= N; t++) {
    int minx = INF, maxx = -INF, miny = INF, maxy = -INF;
    for (int i = 0; i < H; i++) for (int j = 0; j < W; j++) {
      if (B[i][j] == t) {
        minx = min(minx, j);
        maxx = max(maxx, j);
        miny = min(miny, i);
        maxy = max(maxy, i);
      }
    }

    vector<int> pre;
    for (int y = miny; y <= maxy; y++) for (int x = minx; x <= maxx; x++) {
      if (B[y][x] && B[y][x] != t) pre.push_back(B[y][x]);
    }
    compress(pre);

    for (int p : pre) {
      adj[p].push_back(t);
      indegree[t]++;
    }
  }

  queue<int> q;
  for (int i = 1; i <= N; i++) if (!indegree[i]) q.push(i);

  vector<int> ans;
  for (int i = 1; i <= N; i++) {
    int u = q.front(); q.pop();
    ans.push_back(u);

    for (int v : adj[u]) {
      if (--indegree[v] == 0) q.push(v);
    }
  }

  reverse(ans.begin(), ans.end());
  for (int u : ans) cout << u << " ";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
