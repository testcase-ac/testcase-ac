#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 10000;
int A[MAX], dL[MAX], dR[MAX];

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; i++) cin >> A[i];

  dL[0] = 1;
  for (int i = 1; i < N; i++) {
    dL[i] = 1;
    if (A[i - 1] <= A[i]) dL[i] = dL[i - 1] + 1;
  }

  dR[N - 1] = 1;
  for (int i = N - 2; i >= 0; i--) {
    dR[i] = 1;
    if (A[i] >= A[i + 1]) dR[i] = dR[i + 1] + 1;
  }

  int ans = 0;
  for (int i = 0; i < N; i++) {
    ans = max(ans, dL[i] + dR[i] - 1);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
