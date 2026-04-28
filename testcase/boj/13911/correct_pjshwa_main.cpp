#include <bits/stdc++.h>
typedef long long ll;
#define pll pair<ll, ll>
using namespace std;

const ll MAX = 1e18;
bool isMarket[10003];
ll cdist[2][10003];
vector<pll> graph[10003];

void dijk(int d, int s) {
  cdist[d][s] = 0;

  priority_queue<pll, vector<pll>, greater<pll>> pq;
  pq.push({0, s});

  while (!pq.empty()) {
    auto[wi, ui] = pq.top();
    pq.pop();

    if (wi > cdist[d][ui]) continue;

    for (auto &p : graph[ui]) {
      auto[di, vi] = p;
      if (cdist[d][vi] > di + wi) {
        cdist[d][vi] = di + wi;
        pq.push({cdist[d][vi], vi});
      }
    }
  }
}

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int main() {
  fast_io();

  int n, m, x, y, a, b, c;
  cin >> n >> m;

  while (m--) {
    cin >> a >> b >> c;
    graph[a].push_back({c, b});
    graph[b].push_back({c, a});
  }

  // McDonalds, Starbucks dummy node
  b = n + 1;
  c = n + 2;

  cin >> m >> x;
  while (m--) {
    cin >> a;
    isMarket[a] = true;
    graph[b].push_back({0, a});
  }

  cin >> m >> y;
  while (m--) {
    cin >> a;
    isMarket[a] = true;
    graph[c].push_back({0, a});
  }

  isMarket[b] = isMarket[c] = true;

  fill(cdist[0], cdist[0] + n + 3, MAX);
  fill(cdist[1], cdist[1] + n + 3, MAX);

  dijk(0, b);
  dijk(1, c);

  ll mv = MAX;
  for (int i = 1; i <= n; i++) {
    if (isMarket[i] || cdist[0][i] > x || cdist[1][i] > y) continue;
    mv = min(mv, cdist[0][i] + cdist[1][i]);
  }

  cout << (mv == MAX ? -1 : mv) << '\n';
}
