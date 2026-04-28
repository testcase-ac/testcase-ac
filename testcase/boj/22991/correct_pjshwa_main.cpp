#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  int n, m;
  cin >> n >> m;
  vector<pii> a(n), b(m);
  for (int i = 0; i < n; i++) cin >> a[i].first >> a[i].second, a[i].second *= -1;
  for (int i = 0; i < m; i++) cin >> b[i].first >> b[i].second;
  sort(a.rbegin(), a.rend());
  sort(b.rbegin(), b.rend());

  int j = 0, ans = 0;
  multiset<int> operable;
  for (int i = 0; i < n; i++) {
    auto [w, t] = a[i];
    while (j < m && b[j].first >= w) operable.insert(b[j++].second);

    auto it = operable.upper_bound(-t);
    if (it == operable.begin()) continue;
    operable.erase(--it);
    ans++;
  }

  cout << ans << '\n';
}
