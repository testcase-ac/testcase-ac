#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 50;
int parent[MAX], degree[MAX];

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
  int n, m;
  cin >> n >> m;
  for (int i = 0; i < n; i++) parent[i] = i;

  queue<pii> wait;
  int uc = 0;
  for (int i = 0; i < n; i++) {
    string s;
    cin >> s;
    for (int j = i + 1; j < n; j++) {
      if (s[j] == 'N') continue;

      if (Find(i) == Find(j)) wait.push({i, j});
      else {
        uc++;
        degree[i]++; degree[j]++;
        Union(i, j);
      }
    }
  }

  if (uc < n - 1) return cout << "-1\n", void();
  while (uc < m && !wait.empty()) {
    auto [i, j] = wait.front();
    wait.pop();

    uc++;
    degree[i]++; degree[j]++;
  }

  if (uc == m) {
    for (int i = 0; i < n; i++) cout << degree[i] << ' ';
    cout << '\n';
  }
  else cout << "-1\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
