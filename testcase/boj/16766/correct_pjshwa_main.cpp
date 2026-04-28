#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e5;
int A[MAXN];

void solve() {
  int N, M, C; cin >> N >> M >> C;
  for (int i = 0; i < N; ++i) cin >> A[i];
  sort(A, A + N);

  int l = 1, r = 1e9;
  while (l < r) {
    int m = (l + r) / 2;

    int last_v = A[0], last_i = 0, cnt = 1;
    for (int i = 1; i < N; ++i) {
      if (A[i] - last_v > m || i - last_i == C) {
        last_v = A[i]; last_i = i;
        ++cnt;
      }
    }

    if (cnt <= M) r = m;
    else l = m + 1;
  }

  cout << l << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
