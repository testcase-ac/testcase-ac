#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
int A[MAX], B[MAX];
vector<pii> graph[MAX];
bool vis[MAX];
int tz, az;

void dfs(int v, bool sgn) {
  vis[v] = 1;
  tz++;
  if (sgn) az++;

  for (auto& [u, w] : graph[v]) {
    if (!vis[u]) dfs(u, sgn ^ w);
  }
}

void solve() {
  int N;
  cin >> N;

  map<int, int> t1, t2;
  for (int i = 0; i < N; i++) cin >> A[i], t1[A[i]]++;
  for (int i = 0; i < N; i++) cin >> B[i], t2[B[i]]++;

  for (int i = 0; i < N; i++) {
    if (t1[A[i]] + t2[A[i]] >= 3) return cout << "-1\n", void();
    if (t1[B[i]] + t2[B[i]] >= 3) return cout << "-1\n", void();
  }

  map<int, int> ainv, binv;
  for (int i = 0; i < N; i++) {
    if (ainv.count(A[i])) {
      int u = i, v = ainv[A[i]];
      graph[u].push_back({v, 1});
      graph[v].push_back({u, 1});
    }
    if (ainv.count(B[i])) {
      int u = i, v = ainv[B[i]];
      graph[u].push_back({v, 0});
      graph[v].push_back({u, 0});
    }
    if (binv.count(A[i])) {
      int u = i, v = binv[A[i]];
      graph[u].push_back({v, 0});
      graph[v].push_back({u, 0});
    }
    if (binv.count(B[i])) {
      int u = i, v = binv[B[i]];
      graph[u].push_back({v, 1});
      graph[v].push_back({u, 1});
    }
    ainv[A[i]] = i;
    binv[B[i]] = i;
  }

  int ans = 0;
  for (int i = 0; i < N; i++) {
    if (vis[i]) continue;
    tz = az = 0;
    dfs(i, 1);
    ans += min(az, tz - az);
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
