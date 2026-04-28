#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, P; cin >> N >> P;

  vector<int> A(N); int sumA = 0;
  for (int i = 0; i < N; ++i) cin >> A[i], sumA += A[i];

  int gcdA = A[0];
  for (int i = 1; i < N; ++i) gcdA = gcd(gcdA, A[i]);

  vector<int> Ap(N);
  for (int i = 0; i < N; ++i) Ap[i] = A[i] / gcdA;

  vector<int> B(N); int sumB = 0;
  for (int i = 0; i < N; ++i) cin >> B[i], sumB += B[i];

  int gcdB = B[0];
  for (int i = 1; i < N; ++i) gcdB = gcd(gcdB, B[i]);

  vector<int> Bp(N);
  for (int i = 0; i < N; ++i) Bp[i] = B[i] / gcdB;

  ll Bmul = 1;
  for (int i = 0; i < N; ++i) {
    if (Ap[i] == 0) continue;
    Bmul = max(Bmul, (ll)(Ap[i] + Bp[i] - 1) / Bp[i]);
  }

  cout << sumA / gcdA << ' ' << sumB * Bmul / gcdB << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
