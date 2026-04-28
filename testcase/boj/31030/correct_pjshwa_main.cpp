#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 5000;
ll A[MAXN + 1], X[MAXN + 1];
vector<vector<int>> cycles;
bool vis[MAXN + 1];

void solve() {
  int N; cin >> N;
  for (int i = 1; i <= N; ++i) cin >> A[i];
  for (int i = 1; i <= N; ++i) cin >> X[i];

  for (int i = 1; i <= N; ++i) {
    if (vis[i]) continue;

    int s = i;
    vector<int> cycle;
    while (!vis[s]) {
      vis[s] = true;
      cycle.push_back(s);
      s = A[s];
    }

    cycles.push_back(cycle);
  }

  ll ans = 0;
  for (auto& cycle_g : cycles) {
    ll cur_g = 0;
    for (auto& cycle_f : cycles) {
      int gz = cycle_g.size(), fz = cycle_f.size();
      if (gz % fz != 0) continue;

      for (int d = 0; d < fz; ++d) {
        ll cur = 0;
        for (int i = 0; i < gz; ++i) {
          cur += X[cycle_g[i]] * cycle_f[(i + d) % fz];
        }
        cur_g = max(cur_g, cur);
      }
    }
    ans += cur_g;
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
