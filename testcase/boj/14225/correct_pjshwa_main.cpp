#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 20;
int a[MAX];
int t[2'000'001];
int n, s;

void dfs(int i) {
  if (i == n) return t[s]++, void();

  s += a[i];
  dfs(i + 1);
  s -= a[i];
  dfs(i + 1);
}

void solve() {
  cin >> n;
  for (int i = 0; i < n; i++) cin >> a[i];
  dfs(0);

  for (int j = 1; j <= (1 << n); j++) {
    if (t[j] == 0) return cout << j << '\n', void();
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
