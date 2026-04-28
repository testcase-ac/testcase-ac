#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;
using tll = tuple<ll, ll, ll>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2e6, MAXV = 1e4 + 1;
const ll INF = 1e18;
ll cdist[MAX + 1];
vector<tll> graph[MAX + 1];
int K;

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
    for (auto &[v, l, c] : graph[u]) {
      if (p + c > K) continue;

      int x = v * MAXV + p + c;
      if (cdist[x] > l + w) {
        cdist[x] = l + w;
        pq.push({cdist[x], x});
      }
    }
  }
}

void solve() {
  int N, R;
  cin >> K >> N >> R;
  while (R--) {
    int s, d, l, t;
    cin >> s >> d >> l >> t;
    graph[s].push_back({d, l, t});
  }
  dijk(MAXV);

  ll ans = INF;
  for (int c = 0; c <= K; c++) {
    int x = N * MAXV + c;
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
