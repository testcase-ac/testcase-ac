#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 2e5, MAXV = 1e6;
int A[MAX], C[MAXV + 1];

void solve() {
  int N, M; cin >> N >> M;
  for (int i = 0; i < N; i++) cin >> A[i];

  int L = (9 * M - 1) / 10 + 1;
  for (int i = 0; i < N; i++) {
    C[A[i]]++;
    if (i >= M) C[A[i - M]]--;
    if (C[A[i]] == L) return void(cout << "YES\n");
  }
  cout << "NO\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
