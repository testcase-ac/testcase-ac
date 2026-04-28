#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e5;
int C1[MAXN], C2[MAXN];

void solve() {
  int N; string S; cin >> N >> S;

  vector<int> O, E;
  for (int i = 2 * N; i >= 1; --i) {
    if (i & 1) O.push_back(i);
    else E.push_back(i);
  }

  for (int i = 0; i < N; ++i) {
    if (S[i] == 'O') {
      if (O.empty() || E.empty()) return cout << "NO\n", void();
      C1[i] = O.back(); O.pop_back();
      C2[i] = E.back(); E.pop_back();
    } else {
      vector<int>& V = O.size() >= E.size() ? O : E;
      if (V.size() < 2) return cout << "NO\n", void();
      C1[i] = V.back(); V.pop_back();
      C2[i] = V.back(); V.pop_back();
    }
  }

  cout << "YES\n";
  for (int i = 0; i < N; ++i) cout << C1[i] << ' ' << C2[i] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
