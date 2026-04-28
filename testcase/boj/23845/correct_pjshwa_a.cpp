#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int n; cin >> n;
  multiset<int> m;
  for (int i = 0; i < n; i++) {
    int x; cin >> x;
    m.insert(x);
  }

  ll ans = 0;
  while (!m.empty()) {
    int s = *m.begin(), e = s;

    while (m.find(e) != m.end()) {
      m.erase(m.find(e));
      e++;
    }

    ans += (ll)(e - 1) * (e - s);
  }

  cout << ans << '\n';
}

// 1. TC 간 전역 변수 초기화
// 2. int overflow 체크
// 3. edge case 체크
// 4. 자주 하는 실수
//    - long long에 sqrt() 사용
//    - multiset::count() 사용
int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
