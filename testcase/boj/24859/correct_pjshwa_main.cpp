#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 2e5;
int A[MAXN], Lmin[MAXN], Lmax[MAXN], Rmin[MAXN], Rmax[MAXN];

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; ++i) cin >> A[i];

  Lmin[0] = Lmax[0] = A[0]; Rmin[N - 1] = Rmax[N - 1] = A[N - 1];
  for (int i = 1; i < N; ++i) {
    Lmin[i] = min(Lmin[i - 1], A[i]);
    Lmax[i] = max(Lmax[i - 1], A[i]);
  }
  for (int i = N - 2; i >= 0; --i) {
    Rmin[i] = min(Rmin[i + 1], A[i]);
    Rmax[i] = max(Rmax[i + 1], A[i]);
  }

  cout << "1.0 ";
  for (int i = 1; i < N; ++i) {
    int lmax = Lmax[i - 1], lmin = Lmin[i - 1];
    int rmax = Rmax[i], rmin = Rmin[i];
    double r1 = (double)max(rmax - lmax, 0) / rmax;
    double r2 = (double)max(rmin - lmin, 0) / rmin;
    cout << fixed << setprecision(10) << max(r1, r2) << ' ';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
