#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1000;
ll A[MAX][MAX];

void solve() {
  int N, M; cin >> N >> M;
  for (int i = 0; i < M; i++) for (int j = 0; j < N; j++) cin >> A[j][i];

  vector<ll> F(N); ll dist = 0;
  for (int j = 0; j < N; j++) {
    sort(A[j], A[j] + M);
    F[j] = A[j][M / 2];

    for (int i = 0; i < M; i++) dist += abs(A[j][i] - F[j]);
  }

  cout << dist << '\n';
  for (int j = 0; j < N; j++) cout << F[j] << ' ';
  cout << '\n';
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
