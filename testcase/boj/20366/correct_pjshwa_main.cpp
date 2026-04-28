#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 600;
int A[MAX];

void solve() {
  int N;
  cin >> N;
  for (int i = 0; i < N; i++) cin >> A[i];
  sort(A, A + N);

  int ans = INT_MAX;
  for (int s1 = 0; s1 < N - 3; s1++) for (int s2 = s1 + 3; s2 < N; s2++) {
    int sp = s1 + 1, ep = s2 - 1, oval = A[s1] + A[s2];

    while (sp < ep) {
      int cval = A[sp] + A[ep];
      int diff = cval - oval;
      ans = min(ans, abs(diff));

      if (diff > 0) ep--;
      else sp++;
    }
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
