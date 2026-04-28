#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  int n, x;
  cin >> n >> x;
  ll lb = 0, ub = 1e18;
  bool dir = true;
  ll lcoef = x, ocoef;
  for (int i = 0; i < n - 1; i++) {
    cin >> x;
    ll ocoef = 2 * x - lcoef;
    if (dir) ub = min(ub, (ocoef - lcoef) / 2);
    else lb = max(lb, (lcoef - ocoef) / 2);
    lcoef = ocoef;
    dir = !dir;
  }
  cout << max(0LL, ub - lb + 1) << '\n';
}
