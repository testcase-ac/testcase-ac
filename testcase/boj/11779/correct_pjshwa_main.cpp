#include <bits/stdc++.h>
typedef long long ll;
#define pll pair<ll, ll>
using namespace std;

const int MAX = 1000;
const ll INF = 1e14;
ll cdist[MAX + 1];
int from[MAX + 1];
vector<pll> graph[MAX + 1];

void dijk(int s) {
  cdist[s] = 0;

  priority_queue<pll, vector<pll>, greater<pll>> pq;
  pq.push({0, s});

  while (!pq.empty()) {
    auto[wi, ui] = pq.top();
    pq.pop();

    if (wi > cdist[ui]) continue;

    for (auto &p : graph[ui]) {
      auto[vi, di] = p;
      if (cdist[vi] > di + wi) {
        cdist[vi] = di + wi;
        from[vi] = ui;
        pq.push({cdist[vi], vi});
      }
    }
  }
}

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  int v, e;
  cin >> v >> e;
  while (e--) {
    int x, y, t;
    cin >> x >> y >> t;
    graph[x].push_back({y, t});
  }
  int sp, ep;
  cin >> sp >> ep;

  fill(cdist, cdist + MAX + 1, INF);
  dijk(sp);

  stack<int> traj;
  int im = ep;
  while (im != sp) {
    traj.push(im);
    im = from[im];
  }
  traj.push(sp);

  cout << cdist[ep] << '\n';
  cout << traj.size() << '\n';
  while (!traj.empty()) {
    cout << traj.top() << ' ';
    traj.pop();
  }
}
