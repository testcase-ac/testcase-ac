#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

bool vis[101], ps[101], ns[101];
int main() {
  fast_io();

  int n, a, g;
  while (1) {
    cin >> n;
    if (!n) break;

    memset(vis, 0, sizeof(vis));
    memset(ps, 0, sizeof(ps));
    memset(ns, 0, sizeof(ns));

    for (int i = 0; i < n; i++) {
      cin >> a;
      for (int j = 1; j <= 100; j++) {
        if (ps[j]) {
          g = gcd(j, a);
          ns[g] = true;
        }
      }
      ns[a] = true;
      for (int j = 1; j <= 100; j++) {
        ps[j] = ns[j];
        vis[j] |= ns[j];
        ns[j] = false;
      }
    }

    int cnt = 0;
    for (int j = 1; j <= 100; j++) {
      if (vis[j]) cnt++;
    }
    cout << cnt << '\n';
  }
}
