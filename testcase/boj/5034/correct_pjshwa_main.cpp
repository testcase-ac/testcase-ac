#include <bits/stdc++.h> 
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 20, INF = 0x3f3f3f3f;
int A[MAX];
int d[7][1 << MAX];

void solve() {
  int N;
  cin >> N;
  for (int i = 0; i < N; i++) cin >> A[i];

  for (int i = 0; i < 7; i++) fill(d[i], d[i] + (1 << N), INF);
  d[0][0] = 0;

  for (int state = 1; state < (1 << N); state++) for (int i = 0; i < N; i++) {
    if (!(state & (1 << i))) continue;

    for (int lee = 0; lee < 7; lee++) {
      int nlee = max(0, A[i] - lee - 1);
      d[nlee][state] = min(d[nlee][state], d[lee][state ^ (1 << i)] + nlee + 1);
    }
  }

  int ans = INF;
  for (int lee = 0; lee < 7; lee++) ans = min(ans, d[lee][(1 << N) - 1]);
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
