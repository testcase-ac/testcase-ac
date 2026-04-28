#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 3e5;
int par[MAX + 1];
vector<int> graph[MAX + 1];

void dfs(int v) {
  for (int d : graph[v]) {
    dfs(d);
    cout << "1 " << d << ' ' << v << '\n';
  }
}

int main() {
  fast_io();

  int n, q;
  cin >> n >> q;
  for (int i = 1; i <= n; i++) cin >> par[i];

  cout << n << ' ' << q << '\n';
  int m;
  cin >> m;
  q -= m;
  while (m--) {
    int v;
    cin >> v;
    cout << "2 " << v << '\n';
  }

  vector<int> s;
  for (int i = 1; i <= n; i++) {
    if (par[i] == i) s.push_back(i);
    else {
      q--;
      graph[par[i]].push_back(i);
    }
  }
  for (int start : s) dfs(start);

  while (q--) cout << "1 " << s.back() << ' ' << s.back() << '\n';
}
