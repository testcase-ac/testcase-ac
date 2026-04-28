#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 100;
int A[MAXN], B[MAXN], U[MAXN];

void solve() {
  int N, P, Q; cin >> N >> P >> Q;
  for (int i = 0; i < N; ++i) cin >> A[i];
  for (int i = 0; i < N; ++i) cin >> B[i];

  int trial = 10000, i = 0;
  while (i < N) {
    if (A[i] == B[i]) ++i;
    else {
      if (trial == 0) break;
      --trial; ++U[i];
      A[i] += P; B[i] += Q;
    }
  }

  if (i == N) {
    cout << "YES\n";
    for (int i = 0; i < N; ++i) cout << U[i] << ' ';
  }
  else cout << "NO\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
