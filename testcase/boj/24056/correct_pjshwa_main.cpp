#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 5e5;
int A[MAXN + 1], B[MAXN + 1], cnt;

void update(int i, int v) {
  if (A[i] == B[i]) --cnt;
  A[i] = v;
  if (A[i] == B[i]) ++cnt;
}

void solve() {
  int N; cin >> N;
  for (int i = 1; i <= N; ++i) cin >> A[i];
  for (int i = 1; i <= N; ++i) cin >> B[i];

  int Z = N;
  while (Z > 0 && A[Z] == B[Z]) --Z;
  if (Z == 0) return cout << "1\n", void();

  sort(A + 1, A + Z);
  for (int i = 1; i <= N; ++i) cnt += A[i] == B[i];

  int newItem = A[Z], loc = Z - 1;
  while (1 <= loc && newItem < A[loc]) {
    update(loc + 1, A[loc]);
    if (cnt == N) return cout << "1\n", void();
    --loc;
  }
  if (loc + 1 != Z) update(loc + 1, newItem);
  
  cout << (cnt == N) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
