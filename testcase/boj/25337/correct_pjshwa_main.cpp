#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2e5;
int parent[MAX + 1], A[MAX + 1], B[MAX + 1];
ll G[MAX + 1];
vector<pii> graph[MAX + 1], cinv[MAX + 1];

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

  if (x != y) parent[y] = x;
}

void solve() {
  int N;
  cin >> N;
  for (int i = 0; i < N - 1; i++) {
    int ui, vi, ci;
    cin >> ui >> vi >> ci;
    graph[ui].push_back({vi, ci});
    graph[vi].push_back({ui, ci});
    cinv[ci].push_back({ui, vi});
  }
  for (int i = 1; i <= N; i++) parent[i] = i;
  for (int i = 1; i <= N; i++) cin >> A[i];
  for (int i = 1; i <= N; i++) cin >> B[i];

  for (int c = 1; c <= MAX; c++) {
    set<int> u;
    map<int, ll> gsum;

    for (auto [ui, vi] : cinv[c]) {
      u.insert(ui);
      u.insert(vi);
      gsum[ui] = A[ui];
      gsum[vi] = A[vi];
    }

    for (auto [ui, vi] : cinv[c]) {
      if (Find(ui) == Find(vi)) continue;
      gsum[Find(ui)] += gsum[Find(vi)];
      Union(ui, vi);
    }

    for (int ui : u) G[ui] += gsum[Find(ui)];
    for (int ui : u) parent[ui] = ui;
  }

  ll minv = 0, maxv = 0;
  sort(G + 1, G + N + 1);
  sort(B + 1, B + N + 1);
  for (int i = 1; i <= N; i++) {
    minv += G[i] * B[N + 1 - i];
    maxv += G[i] * B[i];
  }
  cout << minv << '\n' << maxv << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
