#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int n; cin >> n;
  if (n == 1) return cout << "1\n1 0\n", void();

  vector<pii> ans;
  ans.emplace_back(2, -1);
  ans.emplace_back(1, 0);

  for (int nt = 2; nt <= n; nt++) {
    int ta = 1, tb = 1;
    for (int i = 0; i < n - 1; i++) {
      if (ta == nt - 1) ta++;
      if (tb == nt) tb++;

      ans.emplace_back(ta, nt - 1);
      ans.emplace_back(tb, -nt);

      ta++; tb++;
    }
    ans.emplace_back(nt, 0);
  }
  ans.emplace_back(1, n);

  cout << ans.size() << '\n';
  for (auto& [a, b] : ans) cout << a << ' ' << b << '\n';
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
