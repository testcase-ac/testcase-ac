#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1 << 20;
int cdist[MAX];

void solve() {
  int n, m; cin >> n >> m;
  int mask = (1 << m) - 1;

  vector<int> a(n);
  for (int i = 0; i < n; i++) cin >> a[i];

  memset(cdist, 0x3f, sizeof(cdist));
  queue<int> q;
  for (int i = 0; i < n; i++) {
    q.push(a[i]);
    cdist[a[i]] = 0;
  }

  while (!q.empty()) {
    int cur = q.front(); q.pop();

    for (int b = 0; b < m; b++) {
      int nxt = cur ^ (1 << b);
      if (cdist[nxt] > cdist[cur] + 1) {
        cdist[nxt] = cdist[cur] + 1;
        q.push(nxt);
      }
    }
  }

  for (int i = 0; i < n; i++) {
    cout << m - cdist[a[i] ^ mask] << ' ';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
