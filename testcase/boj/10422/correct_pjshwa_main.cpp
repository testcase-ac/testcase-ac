#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const int MOD = 1e9 + 7;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

ll d[2501];
int main() {
  fast_io();

  int t, l;
  cin >> t;

  d[0] = d[1] = 1;
  for (int i = 2; i <= 2500; i++) {
    for (int j = 0; j < i; j++) d[i] = (d[i] + d[i - j - 1] * d[j]) % MOD;
  }

  while (t--) {
    cin >> l;
    if (l & 1) cout << 0;
    else cout << d[l / 2];
    cout << '\n';
  }
}
