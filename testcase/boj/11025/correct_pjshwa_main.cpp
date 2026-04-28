#include <bits/stdc++.h>
#define ll long long
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int main() {
  fast_io();

  ll n, k;
  cin >> n >> k;
  ll res = 0;

  for (int i = 2; i <= n; i++) res = (res + k) % i;
  cout << res + 1 << '\n';
}
