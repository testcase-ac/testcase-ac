#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const int MOD = 1e9 + 7;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

ll d[10001];
int main() {
  fast_io();

  d[0] = d[1] = 1;
  for (int i = 2; i <= 10000; i++) {
    for (int j = 0; j < i; j++) d[i] = (d[i] + d[i - j - 1] * d[j]) % MOD;
  }

  int l;
  cin >> l;
  cout << d[l];
}
