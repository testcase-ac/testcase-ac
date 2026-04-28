#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
pii a[MAX];

int main() {
  fast_io();

  int n;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> a[i].first, a[i].second = i;
  sort(a, a + n);
  reverse(a, a + n);

  priority_queue<int> pqm;
  priority_queue<int, vector<int>, greater<int>> pqx;

  int ans = 0;
  pqm.push(a[0].second);
  pqx.push(a[0].second);
  for (int i = 1; i < n; i++) {
    auto [cv, ci] = a[i];
    ans = max(ans, cv * (max(abs(ci - pqm.top()), abs(ci - pqx.top())) - 1));
    pqm.push(ci);
    pqx.push(ci);
  }
  cout << ans << '\n';
}
