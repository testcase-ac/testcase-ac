#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

ll dc[10];
ll cc = 0;

ll lpow(ll x, ll y, ll m){
  ll r = 1;
  x %= m;
  while (y) {
    if (y & 1) r = (r * x) % m;
    x = (x * x) % m;
    y >>= 1;
  }
  return r;
}

void count_digits_to(ll n, int dig) {
  if (dig == 1) {
    for (int i = 0; i <= n; i++) dc[i]++;
  }
  else {
    ll pow = lpow(10, dig - 1, 1e18);
    ll fdig = n / pow;
    ll rest = n % pow;

    for (int i = 0; i < fdig; i++) dc[i] += pow;
    dc[fdig] += (rest + 1);
    cc += fdig * (dig - 1) * lpow(10, dig - 2, 1e18);
    count_digits_to(rest, dig - 1);
  }
}

int main() {
  fast_io();

  ll u;
  cin >> u;

  ll udup = u;
  int udig = 0;

  while (u) {
    u /= 10;
    udig++;
  }

  count_digits_to(udup, udig);
  for (int i = 0; i < udig; i++) {
    dc[0] -= lpow(10, i, 1e18);
  }

  for (int i = 0; i < 10; i++) {
    cout << cc + dc[i] << ' ';
  }
  cout << '\n';
}
