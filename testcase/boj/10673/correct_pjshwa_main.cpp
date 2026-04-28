#include <bits/stdc++.h>
#define pll pair<ll, ll>
#define pllpi pair<pll, int>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1000;
const ll INF = 1e14;
pair<ll, ll> cdist[MAX + 1];
vector<pair<int, pair<ll, ll>>> graph[MAX + 1];

void dijk(int s) {
  cdist[s] = {0, 0};

  priority_queue<pllpi, vector<pllpi>, greater<pllpi>> pq;
  pq.push({{0, 0}, s});

  while (!pq.empty()) {
    auto [wi, ui] = pq.top();
    pq.pop();

    if (wi > cdist[ui]) continue;

    for (auto &p : graph[ui]) {
      auto [vi, di] = p;
      pll si = {wi.first + di.first, wi.second + di.second};
      if (cdist[vi] > si) {
        cdist[vi] = si;
        pq.push({cdist[vi], vi});
      }
    }
  }
}

int t[101];
int main() {
  fast_io();

  int a, b, n;
  cin >> a >> b >> n;
  for (int i = 0; i < n; i++) {
    int v, c;
    cin >> v >> c;
    for (int j = 0; j < c; j++) cin >> t[j];
    for (int j = 0; j < c; j++) for (int k = j + 1; k < c; k++) {
      graph[t[j]].push_back({t[k], {v, k - j}});
    }
  }

  for (int i = 0; i <= MAX; i++) cdist[i] = {INF, INF};
  dijk(a);

  if (cdist[b].first == INF) cout << "-1 -1\n";
  else cout << cdist[b].first << ' ' << cdist[b].second << '\n';
}
