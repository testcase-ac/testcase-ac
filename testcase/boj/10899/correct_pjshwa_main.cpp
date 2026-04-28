#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e5;
int A[MAX];

void solve() {
  int P, N; cin >> P >> N;
  for (int i = 0; i < N; i++) cin >> A[i];
  sort(A, A + N);

  int acc = 0, ei = N;
  for (int i = 0; i < N; i++) {
    if (acc + A[i] >= P) {
      ei = i;
      break;
    }
    acc += A[i];
  }

  ll base = P - 1 - acc, ans = 0;
  for (int i = ei - 1; i >= 0; i--) {
    base += A[i];
    ans += base;
  }
  cout << ei << ' ' << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
