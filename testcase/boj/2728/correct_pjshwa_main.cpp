#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using uint = unsigned int;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 30, MAXV = 1000;
uint d[MAX + 1][MAX + 1][MAXV + 1], A[MAX + 1];

void solve() {
  uint N, D;
  cin >> N >> D;
  for (int i = 1; i <= N; i++) cin >> A[i];
  sort(A + 1, A + N + 1);
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
