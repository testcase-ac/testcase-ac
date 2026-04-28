#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

int A[4], B[4], C[4];

bool beats(int* a, int* b) {
  int cnt1 = 0, cnt2 = 0;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      cnt1 += b[i] > a[j];
      cnt2 += a[i] > b[j];
    }
  }
  return cnt1 > cnt2;
}

void solve() {
  for (int i = 0; i < 4; ++i) cin >> A[i];
  for (int i = 0; i < 4; ++i) cin >> B[i];

  for (int i = 1; i <= 10; i++) for (int j = 1; j <= 10; j++)
  for (int k = 1; k <= 10; k++) for (int l = 1; l <= 10; l++) {
    C[0] = i; C[1] = j; C[2] = k; C[3] = l;
    if (beats(A, B) && beats(B, C) && beats(C, A)) return cout << "yes\n", void();
    if (beats(A, C) && beats(C, B) && beats(B, A)) return cout << "yes\n", void();
  }

  cout << "no\n";
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
