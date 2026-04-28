#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 500;
vector<int> adj[MAXN + 1];
int indegree[MAXN + 1];

void solve() {
  int N; cin >> N;
  for (int i = 1; i <= N; ++i) {
    adj[i].clear();
    indegree[i] = 0;
  }
  for (int i = 0; i < N - 1; ++i) {
    int u, v; cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
    indegree[u]++; indegree[v]++;
  }

  for (int i = 1; i <= N; ++i) {
    cout << "i = " << i << ", indegree = " << indegree[i] << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
