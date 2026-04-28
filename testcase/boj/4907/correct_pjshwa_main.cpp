#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

ll walsh_sum(ll n, ll r, ll s, ll e) {
  if (s > e) return 0;
  if (n == 0) return 1;

  ll half = 1LL << (n - 1);
  if (r < half) {
    ll r1 = walsh_sum(n - 1, r, s, min(half - 1, e));
    ll r2 = walsh_sum(n - 1, r, max(0LL, s - half), e - half);
    return r1 + r2;
  }
  else {
    ll r1 = walsh_sum(n - 1, r - half, s, min(half - 1, e));
    ll r2 = walsh_sum(n - 1, r - half, max(0LL, s - half), e - half);
    return r1 - r2;
  }
}

int main() {
  fast_io();

  while (1) {
    ll n, r, s, e;
    cin >> n >> r >> s >> e;
    if (n == -1) break;

    cout << walsh_sum(n, r, s, e) << '\n';
  }
}
