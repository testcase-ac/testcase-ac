#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e5;
int A[MAX];

void solve() {
  int N; cin >> N;

  int sum = 0;
  for (int i = 0; i < N; i++) cin >> A[i], sum += A[i];
  if (sum % 3) return cout << "NO\n", void();

  int p = sum / 3, q = 0;
  for (int i = 0; i < N; i++) q += A[i] / 2;

  if (q >= p) cout << "YES\n";
  else cout << "NO\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
