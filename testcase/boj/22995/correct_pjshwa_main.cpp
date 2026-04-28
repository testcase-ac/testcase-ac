#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int k;
  cin >> k;

  int t = 1;
  while (k > (1 << (t + 1)) - 1) t++;
  k -= ((1 << t) - 1);

  stack<int> rest;
  int r = 1;
  while (k) {
    if (k & 1) rest.push(r);
    r++;
    k >>= 1;
  }

  cout << t + rest.size() << '\n';
  for (int i = 1; i <= t; i++) cout << i << ' ';
  while (!rest.empty()) cout << rest.top() << ' ', rest.pop();
  cout << '\n';
}

int main() {
  fast_io();

  int t;
  cin >> t;
  while (t--) solve();
}
