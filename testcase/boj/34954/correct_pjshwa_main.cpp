#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e5;
int B[MAXN], F[MAXN];

void solve() {
  int N, M; cin >> N >> M;
  for (int i = 0; i < N; ++i) cin >> B[i];
  for (int i = 0; i < M; ++i) cin >> F[i];
  sort(B, B + N); sort(F, F + M);

  int j = 0, cnt = 0;
  for (int i = 0; i < N; ++i) {
    while (j < M && F[j] <= B[i]) ++j;
    if (j < M) ++cnt, ++j;
  }

  ll ans = 0;
  for (int i = 0; i < cnt; ++i) ans += F[M - 1 - i];
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
