#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int main() {
  fast_io();

  int n, k;
  cin >> n >> k;

  int g = 360, tmp;
  for (int i = 0; i < n; i++) {
    cin >> tmp;
    g = __gcd(g, tmp);
  }

  for (int i = 0; i < k; i++) {
    cin >> tmp;
    cout << (tmp % g == 0 ? "YES" : "NO") << '\n';
  }
}
