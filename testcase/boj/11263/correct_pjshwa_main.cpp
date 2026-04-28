#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

int dfs(int r, int s) {
  if (r == 0) return s == 0;

  int ret = 0;
  for (int i = 0; i < 10; i++) {
    if (s >= i) ret += dfs(r - 1, s - i);
  }
  return ret;
}

int n, s;
void solve() {
  cout << dfs(n, s) << '\n';
}

int main() {
  fast_io();

  while (cin >> n >> s) solve();
}
