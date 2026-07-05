#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

int A[101], B[101];

void solve() {
  int M;
  cin >> M;
  while (M--) {
    int x, y;
    cin >> x >> y;
    A[x]++; B[y]++;

    int a[101], b[101];
    for (int i = 1; i <= 100; i++) a[i] = A[i], b[i] = B[i];

    int l = 1, r = 100, res = 0;
    while (l <= 100) {
      int x = min(a[l], b[r]);
      if (x) res = max(res, l + r);

      a[l] -= x; b[r] -= x;
      if (a[l] == 0) l++;
      if (b[r] == 0) r--;
    }

    cout << res << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
