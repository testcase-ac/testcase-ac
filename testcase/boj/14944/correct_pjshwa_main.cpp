#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e4, INF = 0x3f3f3f3f;
int L[MAX + 1];

void solve() {
  int n, m;
  cin >> n >> m;
  for (int i = 1; i <= n; i++) cin >> L[i], L[i] += L[i - 1];

  int ans = INF;
  while (m--) {
    int a, b, c;
    cin >> a >> b >> c;
    if (a > b) swap(a, b);

    ans = min(ans, L[n] + 2 * c);
    ans = min(ans, L[n] + L[b] - L[a] + c);
    ans = min(ans, L[a] + 2 * (L[n] - L[b]) + L[b] - L[a + 1] + c);
    ans = min(ans, L[b - 1] + 2 * (L[n] - L[b] + c));
    if (b == a + 1) ans = min(ans, L[a] + L[n] - L[b] + c);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
