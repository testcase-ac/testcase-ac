#include <bits/stdc++.h>
#define ll long long
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

ll josephus(ll n, ll k) {
  if (n == 1) return 0;
  if (k == 1) return n - 1;

  if (n > k) {
    ll cnt = n / k;
    ll res = josephus(n - cnt, k);
    res -= n % k;
    if (res < 0) res += n;
    else res += res / (k - 1);
    return res;
  }
  else return (josephus(n - 1, k) + k) % n;
}

int main() {
  fast_io();

  ll n, k;
  cin >> n >> k;
  cout << josephus(n, k) + 1 << '\n';
}
