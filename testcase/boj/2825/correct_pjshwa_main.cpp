#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

ll nC2(ll n) {
  return n * (n - 1) / 2;
}

ll c[1 << 10];
int main() {
  fast_io();

  int n, b;
  string a;
  cin >> n;
  for (int i = 0; i < n; i++) {
    b = 0;
    cin >> a;
    for (int j = 0; j < a.size(); j++) b |= (1 << (a[j] - 48));
    c[b]++;
  }

  ll ans = 0;
  for (int i = 0; i < 1024; i++) for (int j = i; j < 1024; j++) {
    if (i == j) ans += nC2(c[i]);
    else if (i & j) ans += c[i] * c[j];
  }

  cout << ans;
}
