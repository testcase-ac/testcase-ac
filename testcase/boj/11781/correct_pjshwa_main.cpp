#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;
using tll = tuple<ll, ll, ll>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 5000;
const ll INF = 1e18;
vector<tll> graph[MAX + 1];
ll cdist[MAX + 1];
ll Sh, Eh;

void dijk(int s) {
  fill(cdist, cdist + MAX + 1, INF);
  cdist[s] = 0;

  priority_queue<pll, vector<pll>, greater<pll>> pq;
  pq.push({0, s});

  while (!pq.empty()) {
    auto [wi, ui] = pq.top();
    pq.pop();

    if (wi > cdist[ui]) continue;

    for (auto& [vi, di, ti] : graph[ui]) {
      if (ti) {
        ll Rh = min(Eh, wi + di) - max(Sh, wi);
        if (Rh < 0) Rh = 0;
        if (cdist[vi] > wi + di + Rh) {
          cdist[vi] = wi + di + Rh;
          pq.push({cdist[vi], vi});
        }
      }
      else {
        if (cdist[vi] > di + wi) {
          cdist[vi] = di + wi;
          pq.push({cdist[vi], vi});
        }
      }
    }
  }
}

void solve() {
  int N, M;
  cin >> N >> M >> Sh >> Eh;
  while (M--) {
    ll A, B, L, t1, t2;
    cin >> A >> B >> L >> t1 >> t2;

    graph[A].emplace_back(B, 2 * L, t1);
    graph[B].emplace_back(A, 2 * L, t2);
  }

  dijk(1);
  ll ans = 0;
  for (int i = 1; i <= N; i++) ans = max(ans, cdist[i]);

  if (ans & 1) cout << ans / 2 << ".5\n";
  else cout << ans / 2 << "\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
