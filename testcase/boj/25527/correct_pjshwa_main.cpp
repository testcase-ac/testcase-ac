#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

int n;
void solve() {
  vector<int> v(n + 1);
  for (int i = 1; i <= n; i++) cin >> v[i];

  int ans = 0;
  for (int i = 2; i <= n - 1; i++) {
    if (v[i] > v[i - 1] && v[i] > v[i + 1]) ans++;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  while (cin >> n) {
    if (n == 0) break;
    solve();
  }
}
