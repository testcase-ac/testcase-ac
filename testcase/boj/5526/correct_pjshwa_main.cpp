#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1000;
int a[MAX];

int main() {
  fast_io();

  int n, m;
  cin >> n >> m;
  for (int i = 0; i < n; i++) cin >> a[i];

  set<int> s2;
  s2.insert(0);
  for (int i = 0; i < n; i++) s2.insert(a[i]);
  for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) s2.insert(a[i] + a[j]);

  int ans = 0;
  for (int e : s2) {
    if (e > m) break;
    auto it = s2.upper_bound(m - e);
    it--;
    ans = max(ans, e + *it);
  }
  cout << ans << '\n';
}
