#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const int MOD = 1e9 + 7;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

ll d[5002];
int main() {
  fast_io();

  d[0] = d[1] = 1;
  for (int i = 2; i <= 5001; i++) {
    for (int j = 0; j < i; j++) d[i] = (d[i] + d[i - j - 1] * d[j]) % MOD;
  }

  int t, l;
  cin >> t;
  while (t--) {
    cin >> l;
    cout << d[l + 1] << '\n';
  }
}
