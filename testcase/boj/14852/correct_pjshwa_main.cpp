#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

ll d[1000001];
int main() {
  fast_io();

  d[0] = 1;
  d[1] = 2;
  d[2] = 7;
  d[3] = 22;

  ll mod = 1e9 + 7;
  for (int i = 4; i <= 1e6; i++) d[i] = (2 * d[i - 1] + 4 * d[i - 2] + (mod - 1) * d[i - 4]) % mod;

  ll n;
  cin >> n;
  cout << d[n] << '\n';
}
