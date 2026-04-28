#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 5000, INF = 0x3f3f3f3f;
int cdist[MAX + 1], vis[MAX + 1], X, G;
int sum[MAX + 1], prod3[MAX + 1], smallest[MAX + 1], f[MAX + 1];


int sum_x(int n) {
  int ret = 0;
  for (char& c : to_string(n)) ret += c - '0';
  return ret;
}

int prod3_x(int n) {
  priority_queue<int, vector<int>, greater<int>> pq;
  for (char& c : to_string(n)) {
    pq.push(c - '0');
    if (pq.size() > 3) pq.pop();
  }

  int ret = 1;
  while (!pq.empty()) {
    ret *= pq.top();
    pq.pop();
  }
  return ret;
}

int smallest_x(int n) {
  int ret = 10;
  for (char& c : to_string(n)) {
    ret = min(ret, c - '0');
  }
  return ret;
}

int first_x(int n) {
  return to_string(n).front() - '0';
}

int at(int x, int y) {
  if (x <= MAX && y <= MAX) return 5 * prod3[x] + f[x] * sum[y] + smallest[y];
  return 5 * prod3_x(x) + first_x(x) * sum_x(y) + smallest_x(y);
}

// O(V^2) dijkstra
void dijk(int s) {
  fill(cdist, cdist + MAX + 1, INF);
  memset(vis, 0, sizeof(vis));
  cdist[s] = 1;

  for (int it = 1; it <= MAX; it++) {
    int md = INF, mi = -1;
    for (int vi = 0; vi <= MAX; vi++) {
      if (!vis[vi] && cdist[vi] < md) {
        md = cdist[vi];
        mi = vi;
      }
    }

    if (mi == -1) break;

    vis[mi] = true;
    for (int t : {at(mi, X), at(X, mi)}) {
      if (vis[t]) continue;
      if (cdist[mi] + 1 < cdist[t]) {
        cdist[t] = cdist[mi] + 1;
      }
    }
    for (int vi = 0; vi <= MAX; vi++) {
      if (cdist[vi] == INF) continue;

      for (int t : {at(mi, vi), at(vi, mi)}) {
        if (vis[t]) continue;
        if (cdist[mi] + cdist[vi] + 1 < cdist[t]) {
          cdist[t] = cdist[mi] + cdist[vi] + 1;
        }
      }
    }
  }
}

void solve() {
  cin >> X >> G;
  if (X == G) return cout << "0\n", void();
  if (G > MAX) return cout << "-1\n", void();

  int d[13];
  for (int i = 1; i <= MAX; i++) {
    int x = i, di = 0;
    while (x) {
      d[di++] = x % 10;
      x /= 10;
    }
    f[i] = d[di - 1];

    sort(d, d + di);
    for (int j = 0; j < di; j++) sum[i] += d[j];
    smallest[i] = d[0];
    prod3[i] = 1;
    for (int j = 0; j < 3 && j < di; j++) prod3[i] *= d[di - 1 - j];
  }

  dijk(at(X, X));

  if (cdist[G] == INF) cout << "-1\n";
  else cout << cdist[G] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
