#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e6;
bool C[MAX + 1];
int A[MAX][3];

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < 3; j++) cin >> A[i][j];
  }

  int ans = 0;
  for (int i = 0; i < N; i++) {
    int cnt = 0;
    for (int j = 0; j < 3; j++) {
      if (!C[A[i][j]]) cnt++;
    }
    ans += cnt == 3;
    for (int j = 0; j < 3; j++) C[A[i][j]] = true;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
