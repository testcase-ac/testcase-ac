#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 5000;
int H[MAX + 1];

void solve() {
  int N; cin >> N;
  // for (int i = 0; i < N; i++) cin >> H[i];
  iota(H, H + N, 1);

  do {
    bool f = true;
    for (int i = 1; i < N; i++) {
      if (H[i] + 2 <= H[i - 1]) {
        f = false;
        break;
      }
    }

    if (f) {
      for (int i = 0; i < N; i++) cout << H[i] << " ";
      cout << '\n';
    }

  } while (next_permutation(H, H + N));

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
