#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  int n, q;
  cin >> n >> q;
  vector<ll> a(n);
  for (int i = 0; i < n; ++i) cin >> a[i];
  sort(a.begin(), a.end());

  while (q--) {
    int s, e;
    cin >> s >> e;
    cout << (
      upper_bound(a.begin(), a.end(), e) - lower_bound(a.begin(), a.end(), s)
    ) << '\n';
  }
}
