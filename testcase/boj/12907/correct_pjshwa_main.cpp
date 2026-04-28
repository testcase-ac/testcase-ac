#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  int n;
  cin >> n;
  map<int, int> t;
  for (int i = 0; i < n; i++) {
    int x;
    cin >> x;
    t[x]++;
  }

  if (t[0] == 2) {
    int x = 0;
    while (t[x] == 2) x++;

    int ox = x;
    while (t[x] == 1) x++;

    for (int i = x; i <= 40; i++) {
      if (t[i]) return cout << "0\n", 0;
    }

    ll ans = 1LL << ox;
    if (x > ox) ans *= 2;
    cout << ans << '\n';
  }
  else if (t[0] == 1) {
    int x = 0;
    while (t[x] == 1) x++;

    for (int i = x; i <= 40; i++) {
      if (t[i]) return cout << "0\n", 0;
    }
    cout << "2\n";
  }
  else cout << "0\n";
}
