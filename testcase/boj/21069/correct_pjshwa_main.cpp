#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int n;
  cin >> n;

  int p1 = n, p2 = n + 1;
  set<int> u;

  for (int i = 2; i * i <= p1; i++) {
    if (p1 % i == 0) u.insert(i);
    while (p1 % i == 0) p1 /= i;
  }
  if (p1 > 1) u.insert(p1);
  for (int i = 2; i * i <= p2; i++) {
    if (p2 % i == 0) u.insert(i);
    while (p2 % i == 0) p2 /= i;
  }
  if (p2 > 1) u.insert(p2);

  cout << u.size() << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
