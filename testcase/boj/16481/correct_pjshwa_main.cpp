#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int main() {
  fast_io();

  ll r1, r2, r3;
  cin >> r1 >> r2 >> r3;
  cout << fixed << setprecision(8) << (double)r1 * r2 * r3 / (r1 * r2 + r2 * r3 + r3 * r1) << '\n';
}
