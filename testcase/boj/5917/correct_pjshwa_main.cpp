#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const int MAX = 250;
const ll INF = 1e14;
ll cdist[MAX + 1];
ll graph[MAX + 1][MAX + 1];
int from[MAX + 1];
bool vis[MAX + 1];
int v;

void dijk(int s) {
  fill(cdist, cdist + MAX + 1, INF);
  memset(vis, 0, sizeof(vis));
  cdist[s] = 0;

  for (int it = 1; it <= v - 1; it++) {
    ll md = INF, mi = -1;
    for (int vi = 1; vi <= v; vi++) {
      if (!vis[vi] && cdist[vi] <= md) {
        md = cdist[vi];
        mi = vi;
      }
    }

    vis[mi] = true;
    for (int vi = 1; vi <= v; vi++) {
      if (!vis[vi] && cdist[mi] + graph[mi][vi] < cdist[vi]) {
        cdist[vi] = cdist[mi] + graph[mi][vi];
        from[vi] = mi;
      }
    }
  }
}

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  int e;
  cin >> v >> e;
  for (int vi = 1; vi <= v; vi++) for (int vj = 1; vj <= v; vj++) graph[vi][vj] = INF;

  while (e--) {
    int x, y, t;
    cin >> x >> y >> t;
    graph[x][y] = graph[y][x] = t;
  }

  dijk(1);

  vector<int> traj;
  int im = v;
  while (im != 1) {
    traj.push_back(im);
    im = from[im];
  }
  traj.push_back(1);

  ll ov = cdist[v], nv = 0;
  for (int i = 0; i < traj.size() - 1; i++) {
    int v1 = traj[i], v2 = traj[i + 1];
    graph[v1][v2] *= 2;
    graph[v2][v1] *= 2;
    dijk(1);
    nv = max(nv, cdist[v]);
    graph[v1][v2] /= 2;
    graph[v2][v1] /= 2;
  }

  cout << nv - ov << '\n';
}
