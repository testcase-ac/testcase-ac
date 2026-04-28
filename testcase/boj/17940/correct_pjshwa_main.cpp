#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1000, INF = 0x3f3f3f3f;
vector<tii> graph[MAX];
pii cdist[MAX];

void dijk(int s) {
  for (int i = 0; i < MAX; i++) cdist[i] = {INF, INF};
  cdist[s] = {0, 0};

  priority_queue<tii, vector<tii>, greater<tii>> pq;
  pq.push({0, 0, s});

  while (!pq.empty()) {
    auto [xi, wi, ui] = pq.top();
    pq.pop();

    if (pii(xi, wi) > cdist[ui]) continue;

    for (auto& [ax, aw, av] : graph[ui]) {
      pii nw = {xi + ax, wi + aw};
      if (pii(nw) < cdist[av]) {
        cdist[av] = nw;
        pq.push({nw.first, nw.second, av});
      }
    }
  }
}
void solve() {
  int N, E;
  cin >> N >> E;
  vector<int> S(N);
  for (int i = 0; i < N; i++) cin >> S[i];

  for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) {
    int x;
    cin >> x;
    if (x == 0) continue;

    graph[i].push_back({S[i] != S[j], x, j});
    graph[j].push_back({S[i] != S[j], x, i});
  }

  dijk(0);
  cout << cdist[E].first << ' ' << cdist[E].second << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
