#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e6;
int a[MAX + 1], parent[MAX + 1];
bool vis[MAX + 1];

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
  for (int i = 1; i <= N; i++) {
    cin >> a[i];
    parent[i] = i;
  }

  for (int i = 1; i <= N; i++) for (int j = i + 1; j <= N; j++) {
    if (a[i] > a[j]) Union(i, j);
  }

  vector<vector<int>> v;
  for (int i = 1; i <= N; i++) {
    if (vis[i]) continue;

    v.push_back(vector<int>());
    int group = Find(i);
    for (int j = 1; j <= N; j++) {
      if (Find(j) != group) continue;
      v[v.size() - 1].push_back(j);
      vis[j] = true;
    }
  }

  cout << v.size() << '\n';
  for (auto& vv : v) {
    cout << vv.size() << ' ';
    for (int e : vv) cout << e << ' ';
    cout << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
