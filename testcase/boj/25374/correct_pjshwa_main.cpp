#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int A[100];

void solve() {
  int N;
  cin >> N;

  int cut[10] = {0, 4, 11, 23, 40, 60, 77, 89, 96, 100};
  for (int i = 0; i < N; i++) cin >> A[i];
  sort(A, A + N);
  reverse(A, A + N);

  int ans[10];
  for (int i = 1; i <= 9; i++) {
    int c = A[cut[i] - 1];

    ans[i] = N;
    for (int j = 0; j < N; j++) {
      if (A[j] < c) {
        ans[i] = j;
        break;
      }
    }
  }

  for (int i = 9; i >= 2; i--) ans[i] -= ans[i - 1];
  for (int i = 1; i <= 9; i++) cout << ans[i] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
