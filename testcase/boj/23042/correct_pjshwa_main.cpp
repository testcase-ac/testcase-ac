#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MOD = 1e9 + 7;
int bit[31];

int main() {
  fast_io();

  int n, x;
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> x;
    int b = 0;
    while (x) {
      if (x & 1) bit[b]++;
      x >>= 1;
      b++;
    }
  }

  ll ans = 1;
  for (int i = 0; i < n; i++) {
    x = 0;
    for (int j = 0; j <= 30; j++) {
      if (bit[j]) x += (1 << j), bit[j]--;
    }
    ans = (ans * x) % MOD;
  }

  cout << ans;
}
