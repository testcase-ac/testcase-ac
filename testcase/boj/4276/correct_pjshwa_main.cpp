#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

ll dc[10], cc;

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

  ll l, u, ldup, udup, lans, uans;
  while (1) {
    cin >> l >> u;
    if (l == -1) break;

    if (u == 0) {
      cout << "1\n";
      continue;
    }

    udup = u;
    int udig = 0;

    while (u) {
      u /= 10;
      udig++;
    }

    memset(dc, 0, sizeof(dc));
    cc = 0;

    count_digits_to(udup, udig);
    for (int i = 0; i < udig; i++) {
      dc[0] -= lpow(10, i, 1e18);
    }
    uans = cc + dc[0];

    if (l == 0 || l == 1) {
      if (l == 0) uans++;
      cout << uans << '\n';
      continue;
    }

    l--;
    ldup = l;
    int ldig = 0;

    while (l) {
      l /= 10;
      ldig++;
    }

    memset(dc, 0, sizeof(dc));
    cc = 0;

    count_digits_to(ldup, ldig);
    for (int i = 0; i < ldig; i++) {
      dc[0] -= lpow(10, i, 1e18);
    }
    ll lans = cc + dc[0];

    cout << uans - lans << '\n';
  }
}
