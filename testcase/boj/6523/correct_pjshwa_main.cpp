#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  while (1) {
    ll n, a, b;
    cin >> n;
    if (n == 0) break;

    cin >> a >> b;
    unordered_map<int, int> occ;
    occ[0] = 0;

    ll x = b, t = 0;
    while (!occ.count(x)) {
      occ[x] = ++t;
      x = (x * x) % n;
      x = (a * x + b) % n;
    }

    cout << n - t + occ[x] - 1 << '\n';
  }

}
