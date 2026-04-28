#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 100;
char board[MAX + 1][MAX + 1];

void solve() {
  int n; cin >> n;
  if (n == 2) return cout << "-1\n", void();

  for (int i = 0; i < MAX; i++) fill(board[i], board[i] + MAX, '.');

  int s = (n - 1) / 2;
  for (int i = 1; i <= s; i++) board[0][i] = board[i][0] = 'o';

  board[0][0] = 'o';
  if (n % 2 == 0) board[1][1] = 'o';

  cout << "100\n";
  for (int i = MAX - 1; i >= 0; i--) cout << board[i] << '\n';
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
