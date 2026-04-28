#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 100;
bool vis[MAX + 1], fin[MAX + 1];
int from[MAX + 1];
vector<int> graph[MAX + 1];
pii fm[MAX + 1];

pll ext_gcd(ll a, ll b) {
  if (b) {
    auto tmp = ext_gcd(b, a % b);
    return {tmp.second, tmp.first - (a / b) * tmp.second};
  } else return {1, 0};
}


void solve() {
  int n, m;
  cin >> n >> m;

  for (int i = 1; i <= m; i++) cin >> fm[i].first >> fm[i].second;
  for (int i = 1; i <= m; i++) for (int j = i + 1; j <= m; j++) {
    auto [ai, bi] = fm[i];
    auto [aj, bj] = fm[j];

    if (ai == aj) {
      graph[i].push_back(j);
      graph[j].push_back(i);
      continue;
    }

    int a = aj - ai, g = __gcd(bi, bj);
    if (a % g) continue;

    int u = bi / g, v = -bj / g;
    auto [x, y] = ext_gcd(u, v);
    if (u * x + v * y == -1) x = -x, y = -y;
    x *= (a / g); y *= (a / g);

    while (x >= 0 && y >= 0) x -= bj / g, y -= bi / g;
    while (x < 0 || y < 0) x += bj / g, y += bi / g;

    assert(ai + bi * x == aj + bj * y);

    int val = ai + bi * x;

    if (1 <= val && val <= n) {
      graph[i].push_back(j);
      graph[j].push_back(i);
    }
  }

  int s, e;
  cin >> s >> e;

  memset(from, -1, sizeof from);

  queue<int> q;
  for (int i = 1; i <= m; i++) {
    auto [ai, bi] = fm[i];
    if (s >= ai && (s - ai) % bi == 0) {
      q.push(i);
      vis[i] = true;
    }
    if (e >= ai && (e - ai) % bi == 0) fin[i] = true;
  }

  while (!q.empty()) {
    int v = q.front();
    q.pop();

    if (fin[v]) {
      stack<int> traj;
      while (from[v] != -1) {
        traj.push(v);
        v = from[v];
      }
      traj.push(v);

      cout << traj.size() << '\n';
      while (!traj.empty()) {
        cout << traj.top() << '\n';
        traj.pop();
      }
      return;
    }

    for (int d : graph[v]) {
      if (vis[d]) continue;
      vis[d] = true;
      from[d] = v;
      q.push(d);
    }
  }

  cout << "-1\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
