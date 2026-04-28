#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N;

  using T = tuple<int, int, int>;
  vector<T> order;
  for (int i = 0; i < N; ++i) {
    int a, t; cin >> a >> t;
    order.emplace_back(a, i, t);
  }
  sort(order.begin(), order.end());

  priority_queue<T, vector<T>, greater<T>> wait;
  int ctime = 0, ans = 0, l = 0;
  while (1) {
    while (l < N) {
      auto [a, i, t] = order[l];
      if (a <= ctime) {
        wait.emplace(i, t, a);
        ++l;
      }
      else break;
    }

    if (wait.empty()) {
      if (l == N) break;
      ctime = get<0>(order[l]);
    }
    else {
      auto [i, t, a] = wait.top(); wait.pop();
      ans = max(ans, ctime - a);
      ctime += t;
    }
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
