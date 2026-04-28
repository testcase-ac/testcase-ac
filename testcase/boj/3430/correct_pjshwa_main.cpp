#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e6;
int umax[MAX + 1], ans[MAX];

void solve() {
  int n, m;
  cin >> n >> m;

  memset(umax, 0, sizeof(umax));
  memset(ans, 0, sizeof(ans));

  set<int> free;
  bool able = true;

  for (int i = 0; i < m; i++) {
    int x;
    cin >> x;
    if (!able) continue;

    if (x == 0) free.insert(i);
    else {
      auto it = free.lower_bound(umax[x]);
      if (it == free.end()) able = false;
      else {
        ans[*it] = x;
        ans[i] = -1;
        free.erase(it);
        umax[x] = i + 1;
      }
    }
  }

  if (able) {
    cout << "YES\n";
    for (int i = 0; i < m; i++) if (ans[i] != -1) cout << ans[i] << ' ';
    cout << '\n';
  }
  else cout << "NO\n";
}

int main() {
  fast_io();

  int t;
  cin >> t;
  while (t--) solve();
}
