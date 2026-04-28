#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e5;
int a[MAX + 1], b[MAX + 1], S[MAX + 1], T[MAX + 1];
bool vis[MAX + 1];

void solve() {
  int n; cin >> n;
  for (int i = 1; i <= n; ++i) cin >> a[i];
  for (int i = 1; i <= n; ++i) cin >> b[i];
  for (int i = 1; i <= n; ++i) S[a[i]] = S[b[i]] = 1;

  for (int i = 1; i <= n; ++i) {
    if (S[i]) continue;

    int s = i;
    while (a[s] == b[s] && s != 0) {
      T[s] = 1;
      s = a[s];
    }
  }

  int ans = 0;
  for (int i = 1; i <= n; ++i) {
    if (T[i]) continue;
    ans += (a[i] != 0);
    ans += (b[i] != 0);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
