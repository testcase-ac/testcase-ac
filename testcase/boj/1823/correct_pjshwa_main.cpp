#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2000;
ll a[MAX], n;
ll d[MAX][MAX];

ll rec(int l, int r) {
  int t = n - (r - l);
  if (d[l][r] != -1) return d[l][r];

  ll ans;
  if (l == r) ans = a[l] * t;
  else ans = max(
    a[l] * t + rec(l + 1, r),
    a[r] * t + rec(l, r - 1)
  );
  return d[l][r] = ans;
}

int main() {
  fast_io();

  memset(d, -1, sizeof(d));

  cin >> n;
  for (int i = 0; i < n; i++) cin >> a[i];
  cout << rec(0, n - 1) << '\n';
}
