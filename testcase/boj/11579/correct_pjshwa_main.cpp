#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 500;
ll a[MAX][MAX], x[MAX], t[MAX];

void solve() {
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) cin >> a[i][j];
  for (int i = 0; i < n; i++) cin >> t[i];

  memset(x, 0, sizeof(x));
  ll d = 0;
  for (int i = 0; i < n; i++) {
    assert(a[i][i] == 1);
    if (t[i] < x[i]) return cout << "0\n", void();

    ll c = t[i] - x[i];
    d += c;
    for (int j = i; j < n; j++) x[j] += a[i][j] * c;
  }

  if (d > 2e9) cout << "0\n";
  else cout << "1 " << d << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
