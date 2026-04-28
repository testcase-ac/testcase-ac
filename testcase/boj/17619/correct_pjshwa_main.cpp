#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
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
  int n, q;
  cin >> n >> q;

  vector<tii> a(n);
  for (int i = 1; i <= n; i++) {
    int x1, x2, y;
    cin >> x1 >> x2 >> y;
    a[i - 1] = {x1, x2, i};
  }
  sort(a.begin(), a.end(), [] (const tii& a, const tii& b) {
    auto [a1, a2, ai] = a;
    auto [b1, b2, bi] = b;
    if (a1 == b1) return a2 > b2;
    else return a1 < b1;
  });

  stack<tii> t;
  for (int i = 1; i <= n; i++) parent[i] = i;

  for (int i = 0; i < n; i++) {
    auto [a1, a2, ai] = a[i];
    if (!t.empty()) {
      auto [t1, t2, ti] = t.top();
      if (a2 <= t2) Union(ai, ti);
      else {
        if (a1 <= t2) Union(ai, ti);
        t.pop();
        t.push(a[i]);
      }
    }
    else t.push(a[i]);
  }

  while (q--) {
    int x, y;
    cin >> x >> y;
    cout << (Find(x) == Find(y)) << '\n';
  }
}

int main() {
  fast_io();
 
  int t = 1;
  // cin >> t;
  while (t--) solve();
}
