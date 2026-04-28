#include <bits/stdc++.h>
#define ll long long
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

ll lcm(ll x, ll y) { return x / __gcd(x, y) * y; }

int main() {
  fast_io();

  bool able = true;
  ll dsz, msz, dl, mg, tmp;
  ll lim = 1e9;
  cin >> dsz >> msz;
  cin >> dl;
  for (int i = 1; i < dsz; i++) {
    cin >> tmp;
    dl = lcm(dl, tmp);
    if (dl > lim) {
      able = false;
      break;
    }
  }

  if (!able) {
    cout << "0\n";
    return 0;
  }

  cin >> mg;
  for (int i = 1; i < msz; i++) {
    cin >> tmp;
    mg = __gcd(mg, tmp);
  }

  if (mg % dl == 0) {
    ll val = mg / dl;
    ll orig_val = val;
    ll cnt = 1;
    int prime = 2;
    while (prime * prime <= orig_val) {
      ll p_cnt = 1;
      while (val % prime == 0) {
        val /= prime;
        p_cnt++;
      }
      cnt *= p_cnt;
      prime++;
    }
    
    if (val == 1) cout << cnt << '\n';
    else cout << 2 * cnt << '\n';
  }
  else cout << "0\n"; 
}
