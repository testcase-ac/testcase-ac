#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int D, K; string S; cin >> D >> K >> S;

  int ti = -1, allo = 1;
  for (int i = 0; i < D; ++i) {
    if (S[i] == '0') continue;
    if (ti == -1) ti = i;
    allo &= (S[i] == '1');
  }
  if (ti == -1) return cout << S << '\n', void();
  if (!allo) {
    for (ti = D - 1; ti >= 0; --ti) {
      if (S[ti] > '1') break;
    }
  }

  vector<int> U{S[ti] - '0'}; int f = 0;
  while (K--) {
    f = 0;
    if (U.back() == 1) {
      if (U.size() > 1) f = 1, U.pop_back();
      else {
        U.back() = 9;
        continue;
      }
    }
    int t = U.back(); U.pop_back();
    assert(t > 1);
    t *= 9;
    U.push_back(t / 10); U.push_back(t % 10);
    if (f) U.push_back(1);
  }

  cout << S.substr(0, ti);
  for (int u : U) cout << u;
  cout << S.substr(ti + 1) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
