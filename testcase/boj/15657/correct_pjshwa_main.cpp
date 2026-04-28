#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int n, m;
int a[8];
vector<int> current;

void dfs() {
  if (current.size() == m) {
    for (int i = 0; i < m; i++) cout << current[i] << ' ';
    cout << '\n';
    return;
  }

  for (int i = 0; i < n; i++) {
    if (current.size() && current.back() > a[i]) continue;

    current.push_back(a[i]);
    dfs();
    current.pop_back();
  }
}

int main() {
  fast_io();

  cin >> n >> m;
  for (int i = 0; i < n; i++) cin >> a[i];
  sort(a, a + n);
  dfs();
}
