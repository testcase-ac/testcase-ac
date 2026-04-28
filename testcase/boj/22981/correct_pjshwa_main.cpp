#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

ll a[200000];
int main() {
  fast_io();

  int n;
  ll k;
  cin >> n >> k;
  for (int i = 0; i < n; i++) cin >> a[i];
  sort(a, a + n);

  ll mv = k + 1;
  for (int i = 1; i < n; i++) {
    ll lpow = a[0] * i, rpow = a[i] * (n - i);
    ll d = k / (lpow + rpow);
    if (k % (lpow + rpow)) d++;
    mv = min(mv, d);
  }

  cout << mv;
}
