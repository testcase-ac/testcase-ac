#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int n, m; cin >> n >> m;

  int rmax = 0, wmax = 0;
  while (m--) {
    int r, w; cin >> r >> w;
    rmax = max(rmax, r);
    wmax = max(wmax, w);
  }

  if (rmax + wmax > n) cout << "IMPOSSIBLE\n";
  else {
    for (int i = 0; i < rmax; i++) cout << "R";
    for (int i = 0; i < n - rmax; i++) cout << "W";
    cout << '\n';
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
  cin >> t;
  while (t--) solve();
}
