#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 50, MAXR = 10, GOAL = 32;
int V[MAXN + 1], R[MAXR];
vector<pii> adj[MAXN + 1];
int S[4], ans = 0, cur = 0;

int adv(int v, int s, int t) {
  if (v == GOAL || s == t) return v;

  int nu = adj[v][0].first;
  if (adj[v].size() == 2) {
    for (auto& [u, l] : adj[v]) {
      if (s == 0 && l == 0) continue;
      if (s != 0 && l == 1) continue;
      nu = u;
    }
  }
  return adv(nu, s + 1, t);
}

void init() {
  for (int i = 1; i <= 20; i++) {
    V[i] = i * 2;
    adj[i - 1].push_back({i, 0});
  }

  adj[5].push_back({21, 1});
  adj[21].push_back({22, 0}); V[21] = 13;
  adj[22].push_back({23, 0}); V[22] = 16;
  adj[23].push_back({29, 0}); V[23] = 19;

  adj[10].push_back({24, 1});
  adj[24].push_back({25, 0}); V[24] = 22;
  adj[25].push_back({29, 0}); V[25] = 24;

  adj[15].push_back({26, 1});
  adj[26].push_back({27, 0}); V[26] = 28;
  adj[27].push_back({28, 0}); V[27] = 27;
  adj[28].push_back({29, 0}); V[28] = 26;

  adj[29].push_back({30, 0}); V[29] = 25;
  adj[30].push_back({31, 0}); V[30] = 30;
  adj[31].push_back({20, 0}); V[31] = 35;
  adj[20].push_back({GOAL, 0});
}

void rec(int t) {
  if (t == MAXR) {
    ans = max(ans, cur);
    return;
  }

  for (int p = 0; p < 4; ++p) {
    int pre = S[p], nxt = adv(S[p], 0, R[t]), ok = 1;
    if (pre == GOAL) continue;

    for (int op = 0; op < 4; ++op) {
      if (p != op && nxt != GOAL && S[op] == nxt) ok = 0;
    }
    if (!ok) continue;

    S[p] = nxt;
    cur += V[nxt];
    rec(t + 1);
    cur -= V[nxt];
    S[p] = pre;
  }
}

void solve() {
  init();
  for (int r = 0; r < 10; ++r) cin >> R[r];
  rec(0);
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
