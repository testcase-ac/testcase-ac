#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

int L[26];

void solve() {
  string S; cin >> S;
  memset(L, -1, sizeof(L));

  int n = S.size(), ans = 0;
  for (int i = 0; i < n; i++) {
    int c = S[i] - 'a';

    for (int j = 0; j < 26; j++) {
      if (L[j] == -1) continue;
      if (c == j) continue;
      if (L[c] != -1 && L[j] < L[c]) continue;
      ans++;
    }
    L[c] = i;
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
