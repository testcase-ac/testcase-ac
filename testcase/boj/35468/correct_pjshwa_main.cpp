#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 5e5;
int A[MAXN];

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; ++i) cin >> A[i];

  int d = 0, o = 0, m = 0;
  for (int i = 0; i < N; ++i) {
    int j = N - 1 - i;
    if (i >= j) {
      if (i == j && A[i] == 0) ++m;
      break;
    }
    if (A[i] != A[j]) ++d;
    else if (A[i] == 0) ++o;
  }

  int ok = 1;
  if (d > 2) ok = 0;
  if (d > 0 && o > 0) ok = 0;
  if (m > 0 && d > 1) ok = 0;
  if (m > 0 && d == 0 && o > 0) ok = 0;
  cout << (ok ? "DALGU" : "PONIX") << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
