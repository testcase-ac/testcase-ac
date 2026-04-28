#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int n, a[10000];

void dfs(int s, int e) {
  if (s < e) {
    int o = s + 1;
    while (o <= e && a[o] < a[s]) o++;

    if (o > s + 1) dfs(s + 1, o - 1);
    if (o <= e) dfs(o, e);
  }

  cout << a[s] << '\n';
}

int main() {
  fast_io();

  int x;
  while (cin >> x) a[n++] = x;
  dfs(0, n - 1);
}
