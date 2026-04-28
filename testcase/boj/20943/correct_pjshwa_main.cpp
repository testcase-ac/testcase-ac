#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(false);
}

ll nC2(ll n) {
  return n * (n - 1) / 2;
}

int main() {
  fast_io();

  ll n, a, b, c;
  cin >> n;

  map<pair<int, int>, int> pc;
  for (int i = 0; i < n; i++) {
    cin >> a >> b >> c;
    if (a == 0) pc[{0, 1}]++;
    else if (b == 0) pc[{1, 0}]++;
    else {
      ll g = __gcd(abs(a), abs(b));
      if (a * b < 0) pc[{abs(a) / g, -abs(b) / g}]++;
      else pc[{abs(a) / g, abs(b) / g}]++;
    }
  }

  ll s = nC2(n);
  for (auto [p, c] : pc) s -= nC2(c);
  cout << s;
}
