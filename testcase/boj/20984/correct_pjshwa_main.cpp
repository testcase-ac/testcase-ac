#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 2e5;
ll A[MAX + 10], BL[MAX + 10], BR[MAX + 10], BL_COST[MAX + 10], BR_COST[MAX + 10];

void solve() {
  int N; cin >> N;
  for (int i = 1; i <= N; i++) cin >> A[i];

  for (int i = 1; i <= N; i++) {
    BL_COST[i] = BL_COST[i - 1] + max(0LL, A[i - 1] - A[i] + 1);
    BL[i] = A[i] + BL_COST[i];
  }
  for (int i = N; i >= 1; i--) {
    BR_COST[i] = BR_COST[i + 1] + max(0LL, A[i + 1] - A[i] + 1);
    BR[i] = A[i] + BR_COST[i];
  }

  ll ans = min(BL_COST[N], BR_COST[1]);
  for (int i = 1; i <= N; i++) {
    ans = min(ans, max(BL_COST[i], BR_COST[i + 1]) + (BL[i] == BR[i + 1]));
  }
  cout << ans << '\n';
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
