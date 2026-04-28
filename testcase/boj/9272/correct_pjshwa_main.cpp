#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  int n1, n2;
  cin >> n1 >> n2;
  
  ll n = n2 - n1 + 1;
  cout << n * (n - 1) / 2 << '\n';
}
