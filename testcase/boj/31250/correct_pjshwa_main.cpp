#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const ll MAXN = 500, MOD = 1e9 + 7, INF = 1e18;
ll A[MAXN + 1];
ll adj[MAXN + 1][MAXN + 1];
priority_queue<pair<ll, int>> U[MAXN + 1];

void solve() {
  ll N, M, K; cin >> N >> M >> K;
  for (int i = 1; i <= N; ++i) cin >> A[i];

  vector<tuple<ll, int, int>> E;
  for (int j = 0; j < M; ++j) {
    int u, v; ll B; cin >> u >> v >> B;
    E.emplace_back(B, u, v);
  }
  sort(E.begin(), E.end());

  memset(adj, -1, sizeof adj);

  int ei = 0;
  while (ei < M && get<0>(E[ei]) == 0) {
    auto [B, u, v] = E[ei++];
    adj[u][v] = max(B, adj[u][v]);
    U[u].emplace(B, v);
  }

  __int128_t u = 1, c = 0;
  while (K) {
    ll next = ei < M ? get<0>(E[ei]) : -1, cu = u;

    vector<__int128_t> cdist(N + 1, -1), cmov(N + 1, -1);
    cdist[cu] = c; cmov[cu] = 0;
    __int128_t gap, gap_mov;

    while (1) {
      int cv = U[cu].empty() ? -1 : U[cu].top().second;
      if (cv == -1) {
        gap = A[cu];
        gap_mov = 1;

        __int128_t steps = K / gap_mov;
        if (next != -1 && gap > 0) steps = min(steps, (next - c) / gap);

        K -= steps;
        c += steps * gap;
        break;
      }
      else if (cdist[cv] != -1) {
        K--;
        c += A[cv];

        gap = cdist[cu] + A[cv] - cdist[cv];
        gap_mov = cmov[cu] + 1 - cmov[cv];
        cu = cv;

        if (next != -1 && c >= next) break;

        __int128_t steps = K / gap_mov;
        if (next != -1 && gap > 0) steps = min(steps, (next - c) / gap);
        // cout << "gap = " << (ll) gap << ", steps = " << (ll) steps << ", c = " << (ll) c << ", K = " << (ll) K << endl;

        K -= steps * gap_mov;
        c += steps * gap;
        break;
      }
      else {
        cdist[cv] = cdist[cu] + A[cv];
        cmov[cv] = cmov[cu] + 1;

        cu = cv;
        c += A[cu];

        if (--K == 0) break;
        if (next != -1 && c >= next) break;
      }
    }

    // cout << "===\n";
    // cout << "u = " << (ll)cu << ", c = " << (ll)c << ", K = " << (ll) K << endl;

    // at most 500 steps
    while (K && c < next) {
      int cv = U[cu].empty() ? -1 : U[cu].top().second;
      if (cv != -1) cu = cv;
      c += A[cu];
      K--;
    }

    u = cu;
    while (ei < M && get<0>(E[ei]) <= c) {
      auto [B, u, v] = E[ei++];
      adj[u][v] = max(B, adj[u][v]);
      U[u].emplace(B, v);
    }

    // cout << "u = " << (ll)u << ", c = " << (ll)c << endl;
  }

  ll au = u, ac = c % MOD;
  cout << au << ' ' << ac << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
