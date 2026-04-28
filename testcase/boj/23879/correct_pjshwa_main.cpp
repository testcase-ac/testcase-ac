#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
int a[MAX], b[MAX];

int main() {
  fast_io();

  int n;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> a[i];

  for (int i = 0; i < n; i++) {
    int x;
    cin >> x;
    a[i] -= x;
    if (a[i] < 0) b[i] = -a[i], a[i] = 0;
  }

  ll ans = 0, ltemp;

  ltemp = 0;
  for (int i = 0; i < n; i++) {
    if (a[i] > ltemp) ans += (a[i] - ltemp);
    ltemp = a[i];
  }

  ltemp = 0;
  for (int i = 0; i < n; i++) {
    if (b[i] > ltemp) ans += (b[i] - ltemp);
    ltemp = b[i];
  }

  cout << ans << '\n';
}
