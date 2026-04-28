#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using matrix = vector<vector<ll>>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
int a[MAX];

void solve() {
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> a[i];

  int m = *min_element(a, a + n), cnt = 0;
  for (int i = 0; i < n; i++) if (a[i] == m) cnt++;

  if (cnt == 1) cout << m;
  else {
    int v = a[0] % m;
    for (int i = 1; i < n; i++) v = max(v, a[i] % m);
    cout << v;
  }
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
