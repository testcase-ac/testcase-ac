#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e5, MOD = 1e9 + 7;
int A[MAXN + 10], B[MAXN + 10];
int Aul[MAXN + 10], Aur[MAXN + 10], Bul[MAXN + 10], Bur[MAXN + 10];

void solve() {
  int N, M, j; cin >> N >> M >> j >> j;
  for (int i = 1; i <= N; ++i) cin >> A[i];
  for (int i = 1; i <= M; ++i) cin >> B[i];
  sort(A + 1, A + N + 1); sort(B + 1, B + M + 1);

  j = 1;
  for (int i = 1; i <= N; ++i) {
    while (j <= M && B[j] < A[i]) ++j;
    Aul[i] = (Aul[i - 1] + j - 1) % MOD;
  }
  j = M;
  for (int i = N; i >= 1; --i) {
    while (j >= 1 && B[j] > A[i]) --j;
    Aur[i] = (Aur[i + 1] + M - j) % MOD;
  }
  j = 1;
  for (int i = 1; i <= M; ++i) {
    while (j <= N && A[j] < B[i]) ++j;
    Bul[i] = (Bul[i - 1] + j - 1) % MOD;
  }
  j = N;
  for (int i = M; i >= 1; --i) {
    while (j >= 1 && A[j] > B[i]) --j;
    Bur[i] = (Bur[i + 1] + N - j) % MOD;
  }

  int ans = 0;
  for (int i = 1; i <= N; ++i) {
    int cur = (Aul[i] - Aul[i - 1] + MOD) % MOD;
    cur = (cur * (ll)Aur[i + 1]) % MOD;
    ans = (ans + cur) % MOD;
  }
  for (int i = 1; i <= M; ++i) {
    int cur = (Bul[i] - Bul[i - 1] + MOD) % MOD;
    cur = (cur * (ll)Bur[i + 1]) % MOD;
    ans = (ans + cur) % MOD;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
