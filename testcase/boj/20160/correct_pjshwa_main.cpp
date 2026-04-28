#include <bits/stdc++.h>
typedef long long ll;
#define pll pair<ll, ll>
using namespace std;

const ll MAX = 1e18;
int n, ypos[10];
ll cdist[10001], ytim[10];
vector<pll> graph[10001];

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

void dijk(int s) {
  fill(cdist + 1, cdist + n + 1, MAX);
  cdist[s] = 0;

  priority_queue<pll, vector<pll>, greater<pll>> pq;
  pq.push({0, s});

  while (!pq.empty()) {
    auto[wi, ui] = pq.top();
    pq.pop();

    if (wi > cdist[ui]) continue;

    for (auto &p : graph[ui]) {
      auto[di, vi] = p;
      if (cdist[vi] > di + wi) {
        cdist[vi] = di + wi;
        pq.push({cdist[vi], vi});
      }
    }
  }
}

int main() {
  fast_io();

  int m, x, y, a, b, c, s;
  cin >> n >> m;

  while (m--) {
    cin >> a >> b >> c;
    graph[a].push_back({c, b});
    graph[b].push_back({c, a});
  }

  for (int i = 0; i < 10; i++) cin >> ypos[i];
  cin >> s;

  memset(ytim, -1, sizeof ytim);

  ytim[0] = 0;
  int prev = 0;
  for (int i = 1; i < 10; i++) {
    dijk(ypos[prev]);
    if (cdist[ypos[i]] == MAX) continue;

    ytim[i] = ytim[prev] + cdist[ypos[i]];
    prev = i;
  }

  dijk(s);

  int mt = n + 1;
  for (int i = 0; i < 10; i++) {
    if (cdist[ypos[i]] <= ytim[i]) mt = min(mt, ypos[i]);
  }

  cout << (mt == n + 1 ? -1 : mt) << '\n';
}
