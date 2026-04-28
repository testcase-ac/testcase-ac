#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int n;
  cin >> n;
  if (n == 1) return cout << "N\n", void();

  priority_queue<int, vector<int>, greater<int>> pq;
  for (int i = 0, x; i < n; i++) {
    cin >> x;
    pq.push(x);
  }

  vector<int> rem;
  while (pq.size() >= 2) {
    if (rem.empty() && pq.size() == 2) return cout << "Y\n", void();

    int a1 = pq.top(); pq.pop();
    int a2 = pq.top(); pq.pop();

    if (a1 == a2) pq.push(a1 + 1);
    else {
      rem.push_back(a1);
      pq.push(a2);
    }
  }
  rem.push_back(pq.top()); pq.pop();

  if (rem.size() == 2) cout << "Y\n";
  else cout << "N\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
