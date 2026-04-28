#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 3e5;
int A[MAX], deg[MAX];
queue<int> qs[MAX + 1];
vector<int> graph[MAX + 1];
int sz[MAX + 1], ans[MAX + 1];

int dfs(int v, int dt) {
  vector<int> h;
  int a = dt;
  for (int u : graph[v]) {
    int o = dfs(u, a);
    h.push_back(o + 1);
    a += o + 1;
    sz[v] += o;
  }
  if (h.empty()) ans[v] = dt + 1;
  else ans[v] = dt + h[0];

  sz[v]++;
  return sz[v];
}

void solve() {
  int N;
  cin >> N;

  map<int, int> r;
  r[1] = 2;
  for (int i = 0; i < N - 1; i++) {
    cin >> A[i];
    if (r[A[i]] == 0) return cout << "-1\n", void();

    r[A[i]]--;
    r[A[i] + 1] += 2;
  }

  int it = 0;
  qs[0].push(0);
  for (int i = 0; i < N - 1; i++) {
    int p = qs[A[i] - 1].front(), v = ++it;
    graph[p].push_back(v);

    deg[p]++;
    if (deg[p] == 2) qs[A[i] - 1].pop();

    qs[A[i]].push(v);
  }

  dfs(0, 0);
  for (int i = 0; i < N; i++) cout << ans[i] << ' ';
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
