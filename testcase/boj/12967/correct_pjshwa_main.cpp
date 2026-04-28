#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

ll cu[1'000'001], a[2'000];
int main() {
  fast_io();

  ll n, k, s;
  cin >> n >> k;

  vector<ll> fs;
  for (int i = 1; i <= k; i++) {
    if (k % i == 0) fs.push_back(i);
  }

  ll cnt = 0;
  for (int i = 0; i < n; i++) cin >> a[i];
  for (int i = 0; i < n; i++) {
    for (auto f : fs) {
      if ((a[i] * f) % k == 0) cnt += cu[f];
    }
    for (int j = 0; j < i; j++) cu[__gcd(k, a[i] * a[j])]++;
  }

  cout << cnt << '\n';
}
