#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  ll n, sum = 0;
  while (1) {
    cin >> n;
    if (n == -1) break;
    sum += n;
  }
  cout << sum << '\n';
}
