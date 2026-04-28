#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e6;
int parent[2 * MAX + 1];

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
  for (int i = 1; i <= MAX; i++) {
    parent[i] = i;
    parent[i + MAX] = i + MAX;
  }

  vector<pii> flowers;
  for (int i = 0; i < N; i++) {
    int x, y;
    cin >> x >> y;
    flowers.emplace_back(x, y);
    Union(x, y + MAX);
  }

  set<int> groups;
  for (int i = 0; i < N; i++) {
    auto [x, y] = flowers[i];
    groups.insert(Find(x));
    groups.insert(Find(y + MAX));
  }

  cout << (groups.size() + 1) / 2 << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
