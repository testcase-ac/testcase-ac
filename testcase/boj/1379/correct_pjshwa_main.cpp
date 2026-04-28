#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
tii a[MAX];
int ans[MAX + 1];

void solve() {
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    int v, s, e;
    cin >> v >> s >> e;
    a[i] = {s, e, v};
  }
  sort(a, a + n);

  priority_queue<pii, vector<pii>, greater<pii>> pq;
  for (int i = 0; i < n; i++) {
    auto& [s, e, v] = a[i];
    if (i == 0) {
      pq.push({e, 1});
      ans[v] = 1;
      continue;
    }

    auto [te, tv] = pq.top();
    if (te <= s) {
      pq.pop();
      ans[v] = tv;
    }
    else ans[v] = pq.size() + 1;
    pq.push({e, ans[v]});
  }

  cout << pq.size() << '\n';
  for (int i = 1; i <= n; i++) cout << ans[i] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
