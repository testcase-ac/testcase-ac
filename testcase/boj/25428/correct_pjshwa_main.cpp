#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
int A[MAX + 1];
vector<int> graph[MAX + 1];
int parent[MAX + 1], usz[MAX + 1];

int Find(int x) {
  if (x == parent[x]) return x;
  else {
    int p = Find(parent[x]);
    parent[x] = p;
    return p;
  }
}

void Union(int x, int y) {
  x = Find(x);
  y = Find(y);

  if (x == y) return;

  parent[y] = x;
  usz[x] += usz[y];
}

void solve() {
  int N;
  cin >> N;
  for (int i = 1; i <= N; i++) cin >> A[i];
  for (int i = 1; i <= N - 1; i++) {
    int u, v;
    cin >> u >> v;
    graph[u].push_back(v);
    graph[v].push_back(u);
  }

  priority_queue<pii> pq;
  for (int i = 1; i <= N; i++) pq.push({A[i], i});
  for (int i = 1; i <= N; i++) parent[i] = i, usz[i] = 1;

  ll ans = 0;
  while (!pq.empty()) {
    auto [c, v] = pq.top(); pq.pop();

    ans = max(ans, (ll)usz[Find(v)] * c);
    for (int u : graph[v]) {
      if (A[u] >= A[v]) Union(v, u);
      ans = max(ans, (ll)usz[Find(v)] * c);
    }
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
