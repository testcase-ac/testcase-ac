#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 5e5;
int a[MAX];

void solve() {
  int n, m, x, y;
  cin >> n >> m;
  for (int i = 0; i < m; i++) cin >> a[i];
  sort(a, a + m);
  cin >> x >> y;

}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
