#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;
using tll = tuple<ll, ll, ll>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
const ll INF = 1e18;
ll cdist[MAX + 1];
vector<tll> graph[MAX + 1];
ll mid;

void dijk(int s) {
  fill(cdist, cdist + MAX + 1, INF);
  cdist[s] = 0;

  priority_queue<pll, vector<pll>, greater<pll>> pq;
  pq.push({0, s});

  while (!pq.empty()) {
    auto [wi, ui] = pq.top();
    pq.pop();

    if (wi > cdist[ui]) continue;

    for (auto& [v, c, t] : graph[ui]) {
      ll cost = mid > t ? c * (mid - t) * (mid - t) : 0;
      if (cdist[v] > cdist[ui] + cost) {
        cdist[v] = cdist[ui] + cost;
        pq.push({cdist[v], v});
      }
    }
  }
}

void solve() {
  int N, M, K;
  cin >> N >> M >> K;
  while (M--) {
    int A, B, C, T;
    cin >> A >> B >> C >> T;
    graph[A].push_back({B, C, T});
    graph[B].push_back({A, C, T});
  }

  ll left = 0, right = 1e5 + 1;
  while (left < right) {
    mid = (left + right) / 2;
    dijk(1);

    if (cdist[N] <= K) left = mid + 1;
    else right = mid;
  }

  cout << left - 1 << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
