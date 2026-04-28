#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e6;
int h[MAX], l[MAX], r[MAX];

void solve() {
  int n;
  ll max_v;
  stack<int> stk;

  cin >> n;

  for (int i = 0; i < n; i++) {
    cin >> h[i];
    l[i] = -1;
    r[i] = n;
  }

  for (int i = 0; i < n; i++) {
    while (!stk.empty() && h[stk.top()] >= h[i]) stk.pop();
    if (!stk.empty()) l[i] = stk.top();
    stk.push(i);
  }
  while (!stk.empty()) stk.pop();

  for (int i = n - 1; i >= 0; i--) {
    while (!stk.empty() && h[stk.top()] >= h[i]) stk.pop();
    if (!stk.empty()) r[i] = stk.top();
    stk.push(i);
  }
  while (!stk.empty()) stk.pop();

  max_v = 0;
  for (int i = 0; i < n; i++) {
    max_v = max(max_v, (ll)h[i] * (r[i] - l[i] - 1));
  }
  cout << max_v << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
