#include <bits/stdc++.h>
#define ll long long
using namespace std;


void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MOD = 1e9 + 7, MAX = 1e6 + 1;
ll d[MAX], ew[MAX];

int main() {
  fast_io();

  ew[1] = 3;
  d[1] = 7;
  for (int i = 2; i < MAX; i++) {
    ew[i] = (d[i - 1] + 2 * ew[i - 1]) % MOD;
    d[i] = (4 * ew[i - 1] + 3 * d[i - 1]) % MOD;
  }

  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    cout << d[n] << '\n';
  }
}
