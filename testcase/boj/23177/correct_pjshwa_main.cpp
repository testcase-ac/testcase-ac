#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1 << 18;
const ll INF = 1e18;
int a[MAX], r[MAX], n, l;
ll cdist[MAX];
vector<pii> graph[MAX];

void dijk(int x) {
  fill(cdist, cdist + n, INF);

  priority_queue<pll, vector<pll>, greater<pll>> pq;
  for (int i = 0; i < n; i++) {
    if (a[i] & (1 << x)) {
      cdist[i] = 0;
      pq.push({0, i});
    }
  }

  while (!pq.empty()) {
    auto [wi, ui] = pq.top();
    pq.pop();

    if (wi > cdist[ui]) continue;

    for (auto &p : graph[ui]) {
      auto [vi, oi] = p;
      ll ndist = wi - (wi % l) + oi;
      if (oi < (wi % l)) ndist += l;

      if (cdist[vi] > ndist) {
        cdist[vi] = ndist;
        pq.push({cdist[vi], vi});
      }
    }
  }
}

int main() {
  fast_io();

  ll t;
  cin >> n >> l >> t;

  for (int i = 0; i < l; i++) {
    int a, b;
    cin >> a >> b;
    graph[b - 1].push_back({a - 1, i});
  }
  for (int i = 0; i < n; i++) cin >> a[i];

  for (int b = 0; b < 8; b++) {
    dijk(b);

    int mask = 1 << b;
    for (int i = 0; i < n; i++) {
      if (cdist[i] < t) r[i] |= mask;
    }
  }

  for (int i = 0; i < n; i++) cout << r[i] << ' ';
  cout << '\n';
}
