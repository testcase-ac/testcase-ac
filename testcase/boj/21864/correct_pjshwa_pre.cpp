#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

__int128_t lpow(__int128_t x, __int128_t y, __int128_t m) {
  __int128_t r = 1;
  x %= m;
  while (y) {
    if (y & 1) r = (r * x) % m;
    x = (x * x) % m;
    y >>= 1;
  }
  return r;
}

vector<__int128_t> ff(2000), pp(2000), qq(2000);
ll pl, m, g;

__int128_t cal(__int128_t h) {

    __int128_t tg = h;
    __int128_t k = 0;
    while (1) {
      __int128_t tgg = tg;
      __int128_t fl = pl;
      for (int i = 0; i < pl; i++) {
        while (tgg % pp[i] == 0) {
          tgg /= pp[i];
          ff[i]++;
        }
              
        if (tgg == 1) {
          fl = i + 1;
          break;
        }
      }

      if (tgg == 1) {
        __int128_t res = 0;
        for (int i = 0; i < fl; i++) {
          res = (res + ff[i] * qq[i]) % (m-1);
          ff[i] = 0;
        }
        return (res - k) % (m-1);
      }
      for (int i = 0; i < fl; i++) ff[i] = 0;
      tg = tg * g % m;
      k++;
    }
}


int main() {

  g = 42;
  m = 1e18;
  m += 31;

  cin >> pl;

  ll p, q;
  for (int i = 0; i < pl; i++) {
    cin >> p >> q;
    pp[i] = p;
    qq[i] = q;
  }

  ll n = 1017894;
  __int128_t an = 837869873246407644LL;

  while (n < 2000500) {
    __int128_t tn = cal(an);
    n++;
    if (n % 100 == 0) cout << n << ' ' << (ll)tn << '\n';
    an = tn;
  }

}
