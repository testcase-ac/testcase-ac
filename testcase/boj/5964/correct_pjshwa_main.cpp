#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const ll MOD = 12345678910;

int main() {
  fast_io();

  int n;
  cin >> n;

  int cnt = 0;
  vector<int> a(n);
  for (int i = 0; i < n; i++) cin >> a[i];

  vector<ll> v(n);
  bool skip = false;
  for (int i = 0; i < n; i++) {
    if (skip) {
      skip = false;
      continue;
    }
    
    if (a[i] == 0) {
      if (a[i + 1] == 1) {
        v[cnt]++;
        skip = true;
      }
      else cnt++;
    }
    else {
      v[cnt - 1] += 2 * v[cnt];
      v[cnt - 1] %= MOD;
      v[cnt] = 0;
      cnt--;
    }
  }
  cout << v[0] % MOD << "\n";
}
