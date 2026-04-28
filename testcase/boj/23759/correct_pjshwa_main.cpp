#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 5e5;
string a[MAX];
int d[MAX], lp[26][10];

void solve() {
  int n, k;
  cin >> n >> k;
  for (int i = 0; i < n; i++) cin >> a[i];
  memset(lp, -1, sizeof(lp));

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < k; j++) {
      int cl = lp[a[i][j] - 'a'][j];
      if (cl == -1) d[i] = max(d[i], 1);
      else d[i] = max(d[i], d[cl] + 1);
      lp[a[i][j] - 'a'][j] = i;
    }
  }
  cout << n - *max_element(d, d + n) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
