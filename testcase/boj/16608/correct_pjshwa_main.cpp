#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 5e5;
char A[MAX + 1];
bool V[MAX + 1];

void solve() {
  int n, c, b, x; cin >> n >> c >> b;
  fill(A, A + n, '0');
  while (b--) cin >> x, V[x - 1] = true;

  int i = 0;
  if (c & 1) A[i] = '1', c--, i += 2;
  else i++;

  while (i < n) {
    if (c == 0) break;
    if (V[i]) {
      i++;
      continue;
    }

    A[i] = '1';
    c -= 2;
    i += 2;
  }

  cout << A << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
