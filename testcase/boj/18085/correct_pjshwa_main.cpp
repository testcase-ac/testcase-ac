#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2e5;
int parent[MAX + 1];

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
  int n;
  cin >> n;
  for (int i = 1; i <= n; i++) parent[i] = i;

  map<int, int> f;
  vector<tii> ans;
  for (int i = 1; i <= n; i++) {
    int mi;
    cin >> mi;
    while (mi--) {
      int di;
      cin >> di;

      if (f.count(di)) {
        int o = f[di];
        if (Find(o) == Find(i)) continue;

        Union(i, o);
        ans.push_back({i, o, di});
      }
      f[di] = Find(i);
    }

  }

  if (ans.size() == n - 1) {
    for (auto [a, b, c] : ans) cout << a << " " << b << " " << c << "\n";
  }
  else cout << "impossible\n";

}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
