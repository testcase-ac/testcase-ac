#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 150;
const ll INF = 1e18;
vector<pii> graph[MAX * MAX];
bool F[MAX];
ll cdist[MAX * MAX];

void dijk(int s) {
  fill(cdist, cdist + MAX * MAX, INF);
  cdist[s] = 0;

  priority_queue<pll, vector<pll>, greater<pll>> pq;
  pq.push({0, s});

  while (!pq.empty()) {
    auto [wi, ui] = pq.top();
    pq.pop();

    if (wi > cdist[ui]) continue;

    for (auto &p : graph[ui]) {
      auto [vi, di] = p;
      if (cdist[vi] > di + wi) {
        cdist[vi] = di + wi;
        pq.push({cdist[vi], vi});
      }
    }
  }
}

int N, M, L, K, A, H;
void solve() {
  memset(F, 0, sizeof(F));
  for (int i = 0; i < N; i++) for (int j = 0; j <= M; j++) graph[i * MAX + j].clear();
  for (int i = 0; i < L; i++) {
    int x;
    cin >> x;
    F[x] = true;
  }
  while (K--) {
    int X, Y, T;
    cin >> X >> Y >> T;
    for (int i = T; i <= M; i++) {
      graph[X * MAX + i].push_back({Y * MAX + i - T, T});
      graph[Y * MAX + i].push_back({X * MAX + i - T, T});
    }
  }
  for (int i = 0; i < N; i++) {
    if (!F[i]) continue;
    for (int j = 0; j < M; j++) graph[i * MAX + j].push_back({i * MAX + j + 1, 1});
  }

  dijk(A * MAX + M);

  ll ans = INF;
  for (int i = 0; i <= M; i++) ans = min(ans, cdist[H * MAX + i]);

  if (ans == INF) cout << "Help!\n";
  else cout << ans << '\n';
}

int main() {
  fast_io();

  while (1) {
    cin >> N >> M >> L >> K >> A >> H;
    if (N == 0) break;
    solve();
  }
}
