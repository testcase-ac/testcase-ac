#include <bits/stdc++.h>
#define ll long long
#define MOD int(1e9 + 7)
using namespace std;

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

void FastIO() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int main() {
  FastIO();

  int n, x, ai, i;
  cin >> n >> x;

  ll res = 0;
  while (n--) {
    cin >> ai >> i;
    res = x * (res + ai) % MOD;
  }

  cin >> ai;
  cout << (res + ai) % MOD << '\n';
}
