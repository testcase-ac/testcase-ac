#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; string S;
  cin >> N >> S;

  string C = "";
  for (int i = 0; i < N; i++) {
    if (i & 1) C += 'O';
    else C += 'I';
  }

  int acc = 0;
  for (int i = 0; i < N; i++) {
    if (S[i] != C[i]) acc++;
  }

  cout << acc << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
