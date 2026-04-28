#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5, MOD = 1e9 + 9;
ll d[MAX + 10];

int main() {
  fast_io();

  d[0] = d[1] = d[2] = d[3] = 1;
  for (int i = 0; i <= MAX; i++) {
    d[i + 2] = (d[i + 2] + d[i]) % MOD;
    d[i + 4] = (d[i + 4] + d[i]) % MOD;
    d[i + 6] = (d[i + 6] + d[i]) % MOD;
  }

  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    cout << d[n] << '\n';
  }
}
