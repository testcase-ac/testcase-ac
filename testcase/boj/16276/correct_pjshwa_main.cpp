#include <bits/stdc++.h> 
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 100, MAXV = 1e6;
int A[MAXN], D[MAXV + 1], N;

void solve() {
  cin >> N;
  for (int i = 0; i < N; ++i) cin >> A[i];
  sort(A, A + N);

  for (int i = 0; i < N; ++i) for (int j = i + 1; j < N; ++j) D[A[j] - A[i]] = 1;

  if (D[0]) cout << "NO\n";
  else {
    int ud = -1;
    for (int d = 1; 1 + d * (N - 1) <= MAXV; ++d) {
      bool ok = true;
      for (int j = 1; j < N; ++j) ok &= !D[d * j];
      if (ok) {
        ud = d;
        break;
      }
    }

    if (ud == -1) cout << "NO\n";
    else {
      cout << "YES\n";
      for (int i = 0; i < N; ++i) cout << 1 + ud * i << ' ';
      cout << '\n';
    }
  }

  for (int i = 0; i < N; ++i) for (int j = i + 1; j < N; ++j) D[A[j] - A[i]] = 0;
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
