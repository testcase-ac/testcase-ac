#include <bits/stdc++.h>
#define ll long long
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

const int MAX = 1e6, MOD = 1e9;
ll a[MAX + 1];
int main() {
  fast_io();

  int n;
  cin >> n;
  a[0] = 1;
  for (int i = 1; i <= n; i++) a[i] = (i * a[i - 1] + ((i & 1) ? -1 : 1)) % MOD;
  cout << a[n];
}
