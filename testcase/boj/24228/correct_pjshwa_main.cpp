#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  ll n, r;
  cin >> n >> r;
  cout << (n - 1) + 2 * r << '\n';
}
