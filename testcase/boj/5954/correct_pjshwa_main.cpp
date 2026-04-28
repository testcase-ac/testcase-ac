#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 250, MOD = 1e6;
int v[MAX];
int d[MAX * 2000 + 1];
bool u[MAX * 2000 + 1];

int main() {
  fast_io();

  int n, sum = 0;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> v[i], sum += v[i];

  d[0] = u[0] = 1;
  for (int i = 0; i < n; i++) {
    for (int j = sum; j >= 0; j--) {
      if (j >= v[i]) {
        d[j] = (d[j] + d[j - v[i]]) % MOD;
        u[j] |= u[j - v[i]];
      }
    }
  }

  int mdiff = 1e9;
  for (int i = 0; i <= sum; i++) {
    if (u[i]) mdiff = min(mdiff, abs(sum - 2 * i));
  }

  cout << mdiff << '\n' << d[(sum - mdiff) / 2] << '\n';
}
