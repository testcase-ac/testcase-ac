#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 100;
int S[MAX + 1], B[MAX + 1], R[MAX + 1];

void solve() {
  int N; cin >> N;
  for (int i = 1; i <= N; i++) cin >> R[i];

  fill(B + 1, B + N + 1, 1);
  for (int i = N; i >= 1; i--) {
    for (S[i] = 1; S[i] <= N + 1; S[i]++) {
      if (S[i] > N) return cout << "IMPOSSIBLE\n", void();

      if (B[S[i]] == 0) continue;
      if (R[i]) R[i]--;
      else break;
    }
    B[S[i]] = 0;
  }

  for (int i = 1; i <= N; i++) cout << S[i] << " \n"[i == N];
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
