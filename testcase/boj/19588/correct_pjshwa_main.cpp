#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
pii a[MAX];
int x[MAX + 1];
ll px[MAX + 1];

void solve() {
  int n, m;
  cin >> n >> m;
  for (int i = 0; i < n; i++) cin >> a[i].first >> a[i].second;
  sort(a, a + n);
  reverse(a, a + n);

  x[0] = 0;
  for (int i = 0; i < n; i++) x[i + 1] = (x[i] ^ a[i].second);
  for (int i = m; i <= n; i++) {
    px[i] = px[i - m] + (x[i] ^ x[i - m]);
  }

  int q;
  cin >> q;
  while (q--) {
    int a, b;
    cin >> a >> b;
    cout << px[a * m + b] - px[b] << '\n';
  }
}

int main() {
  fast_io();
 
  int t = 1;
  // cin >> t;
  while (t--) solve();
}
