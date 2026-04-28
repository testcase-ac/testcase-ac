#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

int P;
void solve() {
  if (P == 2) return cout << "Impossible\n", void();

  vector<int> V(P, 0); int p;
  for (p = 2; p < P; ++p) {
    if (V[p]) continue;

    int i = p, cnt = 0;
    while (i != 1) {
      ++cnt; V[i] = 1;
      i = (i * p) % P;
    }
    if (cnt == P - 2) break;
  }

  string S(P, '0');
  int i = p, f = 1;
  while (i != 1) {
    S[i] = '0' + f;
    f ^= 1;
    i = (i * p) % P;
  }
  for (int i = 1; i < P; ++i) cout << S[i];
  cout << '\n';
}

int main() {
  fast_io();

  while (cin >> P) {
    if (P == 0) break;
    solve();
  }
}
