#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2e5, INF = 1e9 + 7;
int A[MAX + 1];

void solve() {
  int N;
  cin >> N;

  int p;
  for (int i = 0; i < N; i++) {
    cin >> A[i];
    if (A[i] == -1) p = i;
  }

  int a1 = INF, a2 = INF;
  for (int i = 0; i < p; i++) a1 = min(a1, A[i]);
  for (int i = p + 1; i < N; i++) a2 = min(a2, A[i]);

  cout << a1 + a2 << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
