#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MOD = 998244353;
int a[5000];
long long d[5000];

int main() {
  fast_io();

  int n;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> a[i];

  d[0] = 1;
  for (int i = 1; i < n; i++) {
    d[i] = 1;
    for (int j = 0; j < i; j++) if (a[j] < a[i]) d[i] = (d[i] + d[j]) % MOD;
  }

  for (int i = 0; i < n; i++) cout << d[i] << ' ';
}
