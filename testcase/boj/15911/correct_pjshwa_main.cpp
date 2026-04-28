#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, Q;
  cin >> N >> Q;

  int L = 0, S = 0, U = 0;
  vector<double> A(N + 1);
  for (int i = 1; i <= N; ++i) {
    cin >> A[i];
    if (A[i] < 0.5) L++;
    else if (A[i] > 0.5) U++;
    else S++;
  }

  if (S) cout << "SAME\n";
  else if (U & 1) cout << "ALIVE\n";
  else cout << "DEAD\n";

  while (Q--) {
    int x; double p;
    cin >> x >> p;

    if (A[x] < 0.5) L--;
    else if (A[x] > 0.5) U--;
    else S--;

    A[x] = p;

    if (A[x] < 0.5) L++;
    else if (A[x] > 0.5) U++;
    else S++;

    if (S) cout << "SAME\n";
    else if (U & 1) cout << "ALIVE\n";
    else cout << "DEAD\n";
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
