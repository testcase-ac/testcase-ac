#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

int main() {
  fast_io();

  ll d;
  cin >> d;

  double q = sqrt(d);
  cout << fixed << setprecision(10) << 4 * q << '\n';
}
