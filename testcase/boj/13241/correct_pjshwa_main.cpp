#include <bits/stdc++.h>
#define ll long long
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

ll gcd(ll x, ll y){ return y ? gcd(y, x % y) : x; }
ll lcm(ll x, ll y){ return x / gcd(x, y) * y; }

int main() {
  fast_io();

  ll x, y;
  cin >> x >> y;
  cout << lcm(x, y) << '\n';
}
