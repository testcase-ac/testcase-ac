#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 250, INF = 0x3f3f3f3f;

void solve() {
  int N, T; string S;
  cin >> N >> T >> S;

  vector<int> A(N);
  for (int i = 0; i < N; i++) A[i] = S[i] == '1';

  vector<tii> O;
  for (int i = 0; i < T; i++) {
    int t, x, y;
    cin >> t >> x >> y;
    O.emplace_back(t, x - 1, y - 1);
  }
  sort(O.begin(), O.end());

  int cc = 0, mk = INF, xk = -INF;
  for (int z = 0; z < N; z++) {
    if (!A[z]) continue;

    bool f = false;
    for (int pk = 0; pk <= MAX + 1; pk++) {
      vector<int> R(N, -1), C(N);
      R[z] = pk; C[z] = 1;

      for (auto& [_, x, y] : O) {
        if (C[x] && C[y]) {
          if (R[x] > 0) R[x]--;
          if (R[y] > 0) R[y]--;
        }
        else if (C[x]) {
          if (R[x] > 0) {
            R[x]--;
            R[y] = pk;
            C[y] = 1;
          }
        }
        else if (C[y]) {
          if (R[y] > 0) {
            R[y]--;
            R[x] = pk;
            C[x] = 1;
          }
        }
      }

      if (A == C) {
        f = true;
        mk = min(mk, pk);
        xk = max(xk, pk);
      }

    }

    if (f) cc++;
  }

  cout << cc << ' ' << mk << ' ';
  if (xk == MAX + 1) cout << "Infinity\n";
  else cout << xk << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
