#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int a[(int)2e4];
int b[(int)2e4];
int main() {
  fast_io();

  int t, n, m, cnt;
  cin >> t;

  while (t--) {
    cin >> n >> m;
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < m; i++) cin >> b[i];
    sort(b, b + m);

    cnt = 0;
    for (int i = 0; i < n; i++) cnt += lower_bound(b, b + m, a[i]) - b;
    cout << cnt << '\n';
  }
}
