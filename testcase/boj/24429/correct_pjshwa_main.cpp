#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2e5;
pii a[MAX];

int main() {
  fast_io();

  int n;
  cin >> n;
  for (int i = 0; i < n; ++i) cin >> a[i].first >> a[i].second;
  sort(a, a + n);

  vector<pii> segments;
  auto [cs, ce] = a[0];
  for (int i = 1; i < n; ++i) {
    auto [rs, re] = a[i];
    if (rs > ce) {
      segments.push_back({cs, ce});
      cs = rs;
      ce = re;
    }
    else ce = max(ce, re);
  }
  segments.push_back({cs, ce});

  int maxi = 0, sz = segments.size(), ans = 0;
  for (int i = 0; i <= maxi; ++i) {
    auto [rs, re] = segments[i];
    ans = max(ans, re);
    auto it = upper_bound(segments.begin(), segments.end(), pii(re + re - rs, 1e9));
    it--;
    maxi = max(maxi, (int)(it - segments.begin()));
  }

  cout << ans << '\n';
}
