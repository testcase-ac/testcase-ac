#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 2000;
int A[MAX], B[MAX];

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; i++) cin >> A[i];
  for (int i = 0; i < N; i++) cin >> B[i];

  int ans = A[0] * B[0], aB = 0, aE = N - 1;
  auto update_ans = [&](int cur, int cB, int cE) {
    if (cur <= ans) return;
    ans = cur; aB = cB; aE = cE;
  };

  for (int B_base = 0; B_base < N; B_base++) {
    int cur = 0;
    for (int i = B_base; i < N; i++) cur += A[i] * B[N + B_base - i - 1];
    update_ans(cur, B_base, 0);

    int s = B_base, e = N - 1;
    for (int d = 1;; d++) {
      int cB = B_base + d, cE = d;
      if (cB + cE >= N) break;

      cur -= A[s] * B[e];
      cur -= B[s] * A[e];
      update_ans(cur, cB, cE);

      s++, e--;
    }
  }

  for (int E_base = 0; E_base < N; E_base++) {
    int cur = 0;
    for (int i = 0; i < N - E_base; i++) cur += A[i] * B[N - E_base - i - 1];
    update_ans(cur, 0, E_base);

    int s = 0, e = N - E_base - 1;
    for (int d = 1;; d++) {
      int cB = d, cE = E_base + d;
      if (cB + cE >= N) break;

      cur -= A[s] * B[e];
      cur -= B[s] * A[e];
      update_ans(cur, cB, cE);

      s++, e--;
    }
  }

  cout << aB << ' ' << aE << '\n' << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
