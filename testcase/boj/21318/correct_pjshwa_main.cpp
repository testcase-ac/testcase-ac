#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
int a[MAX + 1], p[MAX + 1];

void solve() {
  int n, q;
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> a[i];

  p[1] = 0;
  for (int i = 2; i <= n; i++) {
    p[i] = p[i - 1];
    if (a[i] < a[i - 1]) p[i]++;
  }

  cin >> q;
  while (q--) {
    int l, r;
    cin >> l >> r;
    cout << p[r] - p[l] << '\n';
  }

}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
