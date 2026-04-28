#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MAX = 1e6;
set<int> u[MAX + 1];
bool erased[MAX + 1];

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void erase(int x, int i) {
  u[x].erase(i);
  erased[i] = true;
}

void solve() {
  int n;
  cin >> n;
  priority_queue<pii> pq;
  for (int i = 0; i < n; ++i) {
    int x;
    cin >> x;
    pq.push({x, -i});
    u[x].insert(i);
  }

  int ans = 0;
  while (1) {
    while (!pq.empty() && erased[-pq.top().second]) pq.pop();
    if (pq.empty()) break;

    ans++;
    auto [x, i] = pq.top();
    i = -i;
    pq.pop();
    erase(x, i);

    while (1) {
      x--;
      auto it = u[x].upper_bound(i);
      if (it == u[x].end()) break;

      i = *it;
      erase(x, i);
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
