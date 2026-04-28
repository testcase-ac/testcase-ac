#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

long long f[20];
int main() {
  fast_io();

  long long n;
  cin >> n;

  f[0] = 1;
  for (int i = 1; i < 20; i++) f[i] = f[i - 1] * i;
  for (int i = 19; i >= 0; i--) {
    if (f[i] == n) return cout << "YES", 0;
    if (n > f[i]) n -= f[i];
  }

  cout << "NO";
}
