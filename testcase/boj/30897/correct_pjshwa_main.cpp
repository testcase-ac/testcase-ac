#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 50000;
int A[MAX];

void solve() {
  int N; cin >> N;

  cout << "YES\n";

  bool has_zero = false;
  for (int i = 0; i < N; ++i) {
    cin >> A[i];
    has_zero |= A[i] == 0;
  }

  if (has_zero) {
    cout << A[0];
    for (int i = 1; i < N; ++i) cout << '*' << A[i];
    cout << '\n';
    return;
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
