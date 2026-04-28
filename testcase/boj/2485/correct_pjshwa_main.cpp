#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int v[(size_t)1e5];
int main() {
  fast_io();

  int n;
  cin >> n;

  for (int i = 0; i < n; i++) cin >> v[i];
  sort(v, v + n);

  int gcd_v = v[1] - v[0];
  for (int i = 2; i < n; i++) gcd_v = __gcd(gcd_v, v[i] - v[i - 1]);

  int cnt = 0;
  for (int i = 1; i < n; i++) {
    cnt += ((v[i] - v[i - 1]) / gcd_v - 1);
  }
  cout << cnt << '\n';
}
