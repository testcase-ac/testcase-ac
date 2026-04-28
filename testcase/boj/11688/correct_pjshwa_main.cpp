#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
 
void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int main(){
  fast_io();

  ll a, b, L;
  cin >> a >> b >> L;
  ll g = __gcd(a, b);
  a = a / g * b;

  if (L % a) cout << -1;
  else {
    ll k = L / a;
    ll na = 1;
    b = a;
    for (ll i = 2; i * i <= b; i++) {
      if (b % i == 0) {
        while (b % i == 0) {
          b /= i;
          if (k % i == 0) na *= i;
        }
      }
    }
    if (b > 1 && k % b == 0) na *= b;
    cout << na * k;
  }

}
