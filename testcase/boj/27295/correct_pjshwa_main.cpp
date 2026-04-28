#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  ll n, b; cin >> n >> b;

  ll xsum = 0, ysum = 0;
  for (int i = 0; i < n; i++) {
    int x, y; cin >> x >> y;
    xsum += x;
    ysum += y;
  }

  ll p = ysum - n * b, q = xsum;
  if (q == 0) cout << "EZPZ\n";
  else {
    ll g = __gcd(p, q);
    p /= g; q /= g;
    if (q < 0) p = -p, q = -q;

    if (q == 1) cout << p << '\n';
    else cout << p << '/' << q << '\n';
  }
}

// 1. TC 간 전역 변수 초기화
// 2. int overflow 체크
// 3. edge case 체크
// 4. 자주 하는 실수
//   - long long에 sqrt() 사용
//   - multiset::count() 사용
int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
