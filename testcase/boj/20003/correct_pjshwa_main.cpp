#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

ll lcm(ll x, ll y){ return x / __gcd(x, y) * y; }
ll ns[50], ds[50];
int main() {
  fast_io();

  int n, a, b;
  ll l = 1;

  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> a >> b;
    ns[i] = a;
    ds[i] = b;

    l = lcm(l, b);
  }

  for (int i = 0; i < n; i++) ns[i] *= (l / ds[i]);

  ll g = ns[0];
  for (int i = 1; i < n; i++) g = __gcd(g, ns[i]);

  ll ag = __gcd(g, l);
  cout << g / ag << ' ' << l / ag << '\n';
}
