#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e6;
vector<int> a[MAX];

int main() {
  fast_io();

  int n, m;
  cin >> n >> m;
  for (int i = 0; i < n; i++) a[i].resize(m);
  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) cin >> a[i][j];

  set<int> q;
  for (int j = 0; j < m; j++) {
    for (int i = 0; i < n; i++) q.insert(a[i][j]);
    if (q.size() == j + 1) break;
  }

  cout << q.size() << '\n';
  for (auto x : q) cout << x << ' ';
  cout << '\n';
}
