#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 5e6;
bool u[MAX];
int n, cur = 1;

void dfs(int i) {
  if (i == n) {
    u[cur] = 1;
    return;
  }

  for (int k = 1; k <= 9; k++) {
    cur *= k;
    dfs(i + 1);
    cur /= k;
  }
}

void solve() {
  cin >> n;
  dfs(0);

  int ans = 0;
  for (int i = 0; i < MAX; i++) ans += u[i];
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
