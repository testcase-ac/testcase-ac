#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1000, INF = 1e9 + 7;
pii pos[MAX + 1];
int n, w, d[MAX + 1][MAX + 1];

int dist(pii a, pii b) {
  return abs(a.first - b.first) + abs(a.second - b.second);
}

int r(int a, int b) {
  if (d[a][b] != -1) return d[a][b];

  int cur = max(a, b) + 1;
  if (cur == w + 1) return d[a][b] = 0;

  int res = INF;

  // Car a takes the case
  if (a == 0) res = min(res, r(cur, b) + dist({1, 1}, pos[cur]));
  else res = min(res, r(cur, b) + dist(pos[a], pos[cur]));

  // Car b takes the case
  if (b == 0) res = min(res, r(a, cur) + dist({n, n}, pos[cur]));
  else res = min(res, r(a, cur) + dist(pos[b], pos[cur]));

  return d[a][b] = res;
}

stack<int> traj;
bool trace(int a, int b) {
  int cur = max(a, b) + 1;

  if (cur == w + 1) return d[a][b] == 0;

  // Car a takes the case
  if (a == 0) {
    if (d[a][b] == d[cur][b] + dist({1, 1}, pos[cur])) {
      if (trace(cur, b)) {
        traj.push(1);
        return true;
      }
    }
  }
  else {
    if (d[a][b] == d[cur][b] + dist(pos[a], pos[cur])) {
      if (trace(cur, b)) {
        traj.push(1);
        return true;
      }
    }
  }

  // Car b takes the case
  if (b == 0) {
    if (d[a][b] == d[a][cur] + dist({n, n}, pos[cur])) {
      if (trace(a, cur)) {
        traj.push(2);
        return true;
      }
    }
  }
  else {
    if (d[a][b] == d[a][cur] + dist(pos[b], pos[cur])) {
      if (trace(a, cur)) {
        traj.push(2);
        return true;
      }
    }
  }

  return false;
}

void solve() {
  cin >> n >> w;
  for (int i = 1; i <= w; i++) cin >> pos[i].first >> pos[i].second;

  memset(d, -1, sizeof(d));
  cout << r(0, 0) << '\n';

  trace(0, 0);
  while (!traj.empty()) {
    cout << traj.top() << '\n';
    traj.pop();
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
