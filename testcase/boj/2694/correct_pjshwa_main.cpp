#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int N, S = 0;
  cin >> N;
  vector<int> A(N);
  for (int i = 0; i < N; i++) cin >> A[i], S += A[i];

  int bl = S;
  for (int f = 1; f * f <= S; f++) {
    if (S % f) continue;

    int able, run;
    able = 1, run = 0;
    for (int i = 0; i < N; i++) {
      run += A[i];
      if (run == f) run = 0;
      else if (run > f) {
        able = 0;
        break;
      }
    }

    if (able) {
      cout << f << '\n';
      return;
    }

    able = 1, run = 0;
    for (int i = 0; i < N; i++) {
      run += A[i];
      if (run == S / f) run = 0;
      else if (run > S / f) {
        able = 0;
        break;
      }
    }

    if (able) bl = S / f;
  }

  cout << bl << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
