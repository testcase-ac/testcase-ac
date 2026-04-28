#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  int g, p, x;
  multiset<int> gates;
  cin >> g >> p;
  for (int i = 1; i <= g; i++) gates.insert(i);

  int cnt = 0;
  while (p--) {
    cin >> x;
    auto it = gates.upper_bound(x);
    if (it == gates.begin()) break;

    gates.erase(--it);
    cnt++;
  }

  cout << cnt << '\n';
}
