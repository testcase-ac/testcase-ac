#include <bits/stdc++.h>
#define pii pair<int, int>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 150;
pii a[MAX];

int main() {
  fast_io();

  int n;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> a[i].first >> a[i].second;
  sort(a, a + n, [](pii& a, pii& b) {
    if (a.second == b.second) return a.first > b.first;
    return a.second < b.second;
  });

  int ans = n, r1 = 0, r2 = 0;
  for (int i = 0; i < n; i++) {
    auto [s, e] = a[i];
    if (r1 <= s && r2 <= s) {
      if (r1 < r2) r2 = e;
      else r1 = e;
    }
    else if (r1 <= s) r1 = e;
    else if (r2 <= s) r2 = e;
    else ans--;
  }

  cout << ans << '\n';
}
