#include <bits/stdc++.h> 
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
ll a[MAX], s[MAX];

int main() {
  fast_io();

  int n, q;
  cin >> n >> q;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    s[i] = a[i] * a[i];
    if (i > 0) {
      a[i] += a[i - 1];
      s[i] += s[i - 1];
    }
  }

  while (q--) {
    int l, r;
    cin >> l >> r;
    l--;
    r--;

    ll sum = a[r] - (l > 0 ? a[l - 1] : 0);
    ll sumsq = sum * sum;
    ll sqsum = s[r] - (l > 0 ? s[l - 1] : 0);

    cout << (sumsq - sqsum) / 2 << '\n';
  }
}
