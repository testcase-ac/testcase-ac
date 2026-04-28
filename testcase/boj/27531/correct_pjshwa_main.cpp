#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2e5;
int P[MAX + 1];
vector<int> inv[MAX + 1], adj[MAX + 1];
bool vis[MAX + 1];
vector<int> A;

void dfs(int v) {
  vis[v] = 1;
  A.push_back(P[v]);
  for (int u : adj[v]) {
    if (vis[u]) continue;
    dfs(u);
  }
}

void solve() {
  int N;
  cin >> N;

  for (int i = 1; i <= N; i++) {
    int u, v;
    cin >> u >> v >> P[i];

    inv[u].push_back(i);
    inv[v].push_back(i);
  }

  for (int i = 1; i <= N; i++) {
    if (inv[i].empty()) continue;

    int u = inv[i][0], v = inv[i][1];
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  int ans = 0;
  for (int i = 1; i <= N; i++) {
    if (vis[i]) continue;

    A.clear();
    dfs(i);

    if (A.size() == 1) {
      ans += A[0];
      continue;
    }
    if (A.size() == 2) {
      ans += min(A[0], A[1]);
      continue;
    }
    if (A.size() == 3) {
      ans += A[0] + A[1] + A[2] - max({A[0], A[1], A[2]});
      continue;
    }

    vector<int> A1, A2;
    for (int i = 1; i < A.size(); i++) A1.push_back(A[i]);
    for (int i = 2; i < A.size() - 1; i++) A2.push_back(A[i]);

    int z1 = A1.size();
    vector<int> D1(z1); D1[0] = A1[0];
    for (int i = 1; i < z1; i++) {
      int pre = D1[i - 1];
      pre = min(pre, i > 1 ? D1[i - 2] : 0);
      D1[i] = pre + A1[i];
    }

    int z2 = A2.size();
    vector<int> D2(z2); D2[0] = A2[0];
    for (int i = 1; i < z2; i++) {
      int pre = D2[i - 1];
      pre = min(pre, i > 1 ? D2[i - 2] : 0);
      D2[i] = pre + A2[i];
    }

    int v1 = min(D1[z1 - 1], D1[z1 - 2]), v2;
    if (z2 > 1) v2 = min(D2[z2 - 1], D2[z2 - 2]);
    else v2 = 0;

    ans += min(A[0] + v1, A[1] + A.back() + v2);
  }

  cout << ans << '\n';

}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
