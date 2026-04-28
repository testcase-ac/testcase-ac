#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  string S; cin >> S;
  int N = S.size();

  char l = '0'; int f = 0;
  for (int i = N - 1; i >= 0; i--) {
    if (S[i] < l) {
      char mc = '9' + 1; int mj = -1;
      for (int j = i + 1; j < N; j++) {
        if (S[j] > S[i] && S[j] < mc) mc = S[j], mj = j;
      }
      swap(S[i], S[mj]);
      sort(S.begin() + i + 1, S.end());

      f = 1;
      break;
    }
    else l = S[i];
  }

  if (f) cout << S << '\n';
  else cout << "BIGGEST\n";
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
