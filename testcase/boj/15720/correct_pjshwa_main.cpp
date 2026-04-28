#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int B, C, D; cin >> B >> C >> D;

  int tot = 0; priority_queue<int> p1, p2, p3;
  for (int i = 0, x; i < B; i++) cin >> x, p1.push(x), tot += x;
  for (int i = 0, x; i < C; i++) cin >> x, p2.push(x), tot += x;
  for (int i = 0, x; i < D; i++) cin >> x, p3.push(x), tot += x;

  int dis = tot;
  while (!p1.empty() && !p2.empty() && !p3.empty()) {
    int a = p1.top(), b = p2.top(), c = p3.top();
    dis -= (a + b + c) / 10;
    p1.pop(), p2.pop(), p3.pop();
  }

  cout << tot << '\n' << dis << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
