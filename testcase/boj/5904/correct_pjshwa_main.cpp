#include <bits/stdc++.h>
#define ll long long
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

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

// Size of S(k)
ll s_size(ll k) {
  return lpow(2, k + 3, 1e18) - k - 5;
}

// Char of position n from S(k)
char from_s(ll n, ll k) {
  ll prev_s_size = s_size(k - 1);
  ll curr_s_size = s_size(k);
  if (n <= prev_s_size) return from_s(n, k - 1);
  else if (n + prev_s_size > curr_s_size) return from_s(n - curr_s_size + prev_s_size, k - 1);
  else if (n == 1 + prev_s_size) return 'm';
  else return 'o';
}

int main() {
  fast_io();

  ll n, k = 0;
  cin >> n;

  while (s_size(k) <= n) k++;
  cout << from_s(n, k) << '\n';
}
