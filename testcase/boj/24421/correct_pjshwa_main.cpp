#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 100;
int a[MAX];

void solve() {
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> a[i];

  map<int, int> t;
  int ans = 0;
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      if (a[j] % a[i]) continue;
      ans += t[a[j] / a[i]];
    }
    t[a[i]]++;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
