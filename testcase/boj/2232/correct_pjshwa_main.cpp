#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 50000;
int A[MAX + 10];

void solve() {
  int N; cin >> N;
  for (int i = 1; i <= N; i++) cin >> A[i];

  for (int i = 1; i <= N; i++) {
    if (A[i] >= A[i - 1] && A[i] >= A[i + 1]) {
      cout << i << '\n';
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
