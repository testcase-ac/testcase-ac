#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 3e5;
int u[MAX + 1], c[MAX + 1];

void solve() {
  int n;
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> u[i];

  for (int i = 1; i <= n - 1; i++) {
    if (u[i] < u[i + 1]) {
      c[i]--;
      c[i + 1]++;
    }
    else {
      c[i]++;
      c[i + 1]--;
    }
  }

  deque<pii> v;
  for (int i = 1; i <= n; i++) v.push_back({c[i], i});
  sort(v.begin(), v.end());

  deque<int> q(n);
  for (int i = 0; i < n; i++) cin >> q[i];
  sort(q.begin(), q.end());

  vector<int> ans(n + 1, -1);
  while (!v.empty() && v.back().first >= 1) {
    auto [f, i] = v.back();
    v.pop_back();

    ans[i] = q.back();
    q.pop_back();
  }
  while (!v.empty() && v.front().first <= -1) {
    auto [f, i] = v.front();
    v.pop_front();

    ans[i] = q.front();
    q.pop_front();
  }

  for (int i = 1; i <= n; i++) {
    if (ans[i] != -1) continue;

    if (u[i - 1] < u[i]) {
      ans[i] = q.front();
      q.pop_front();
    }
    else {
      ans[i] = q.back();
      q.pop_back();
    }
  }

  ll val = 0;
  for (int i = 1; i <= n - 1; i++) val += abs(ans[i] - ans[i + 1]);

  cout << val << '\n';
  for (int i = 1; i <= n; i++) cout << ans[i] << ' ';
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
