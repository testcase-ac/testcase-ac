#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1 << 11;
int a[MAX];
vector<int> depth[11];

void r(int s, int e, int d) {
  if (s == e) return;

  int mid = (s + e) / 2;
  depth[d].push_back(a[mid]);

  r(s, mid, d + 1);
  r(mid + 1, e, d + 1);
}

void solve() {
  int k;
  cin >> k;
  for (int i = 0; i < (1 << k) - 1; i++) cin >> a[i];
  r(0, (1 << k) - 1, 0);

  for (int d = 0; d <= 10; d++) {
    if (depth[d].empty()) continue;
    for (int e : depth[d]) cout << e << ' ';
    cout << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
