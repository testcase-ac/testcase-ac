#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int n, m;
  cin >> n >> m;
  priority_queue<int> pq;
  for (int i = 0; i < n; i++) {
    int x;
    cin >> x;
    pq.push(x);
  }
  for (int i = 0; i < m; i++) {
    int x;
    cin >> x;
    if (!pq.empty() && pq.top() >= x) {
      int t = pq.top();
      pq.pop();
      t -= x;
      pq.push(t);
    }
    else return cout << "0\n", void();
  }
  cout << "1\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
