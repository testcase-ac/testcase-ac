// queued_q - 19343122

#include <bits/stdc++.h>
#define endl "\n"
using namespace std;
using lld = long long;
using pii = pair<int, int>;
using pll = pair<lld, lld>;

////////////////////////////////////////////////////////////////
const int MAXN = 2e5+5;
int N, M;
vector<int> adj[MAXN];
int D[MAXN];

void dfs(int u, int p) {
  for (auto v: adj[u]) {
    if (v == p) continue;
    dfs(v, u);
  }
  for (auto v: adj[u]) {
    if (v == p) continue;
    if (D[v] == 0) D[u] = 2;
  }
  if (p == 0 && D[u] == 0) D[u] = 2;
  if (D[u] == 2) {
    for (auto v: adj[u]) {
      if (D[v] == 0) D[v] = 1;
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  ////////////////////////////////

  cin >> N >> M;
  for (int i=0; i<M; i++) {
    int a, b; cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  for (int i=1; i<=N; i++) {
    if (D[i] == 0) dfs(i, 0);
  }

  int ans = 0;
  for (int i=1; i<=N; i++) {
    if (D[i] == 2) ans++;
  }
  cout << ans << endl;

  ////////////////////////////////
  return 0;
}
