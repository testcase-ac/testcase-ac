#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;
using tll = tuple<ll, ll, ll>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 5e5, MAXV = 201;
const ll INF = 1e18;
ll cdist[MAX + 1];
vector<tll> graph[MAX + 1];
int B;

void dijk(int s) {
  fill(cdist, cdist + MAX + 1, INF);
  cdist[s] = 0;

  priority_queue<pll, vector<pll>, greater<pll>> pq;
  pq.push({0, s});

  while (!pq.empty()) {
    auto [w, z] = pq.top();
    pq.pop();

    if (w > cdist[z]) continue;
    
    int u = z / MAXV, p = z % MAXV;
    for (auto& [v, t, h] : graph[u]) {
      if (p - h <= 0) continue;

      int x = v * MAXV + (p - h);
      if (cdist[x] > t + w) {
        cdist[x] = t + w;
        pq.push({cdist[x], x});
      }
    }
  }
}

void solve() {
  int K, N, M, A;
  cin >> K >> N >> M;
  while (M--) {
    int A, B, ti, hi;
    cin >> A >> B >> ti >> hi;
    graph[A].push_back({B, ti, hi});
    graph[B].push_back({A, ti, hi});
  }
  cin >> A >> B;
  dijk(A * MAXV + K);

  ll ans = INF;
  for (int c = 1; c < MAXV; c++) {
    int x = B * MAXV + c;
    ans = min(ans, cdist[x]);
  }

  if (ans == INF) cout << "-1\n";
  else cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
