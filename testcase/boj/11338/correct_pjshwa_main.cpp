#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int n, k;
  cin >> n >> k;

  priority_queue<int, vector<int>, greater<int>> pq;
  int x = 0;

  while (n--) {
    string op;
    cin >> op;
    if (op == "print") cout << x << '\n';
    if (op == "insert") {
      int u;
      cin >> u;
      x ^= u;
      pq.push(u);

      if (pq.size() > k) {
        x ^= pq.top();
        pq.pop();
      }
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
