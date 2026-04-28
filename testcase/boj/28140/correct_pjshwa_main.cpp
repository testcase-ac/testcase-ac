#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, Q; string S; cin >> N >> Q >> S;

  vector<int> Rv, Bv;
  for (int i = 0; i < N; i++) {
    if (S[i] == 'R') Rv.push_back(i);
    if (S[i] == 'B') Bv.push_back(i);
  }
  int Rz = Rv.size(), Bz = Bv.size();

  while (Q--) {
    int l, r, f = 1; cin >> l >> r;

    // Find pattern RRBB
    int rl = lower_bound(Rv.begin(), Rv.end(), l) - Rv.begin();
    if (rl >= Rz - 1) {
      cout << "-1\n";
      continue;
    }

    int bl = lower_bound(Bv.begin(), Bv.end(), Rv[rl + 1]) - Bv.begin();
    if (bl >= Bz - 1 || Bv[bl + 1] > r) {
      cout << "-1\n";
      continue;
    }

    cout << Rv[rl] << ' ' << Rv[rl + 1] << ' ' << Bv[bl] << ' ' << Bv[bl + 1] << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
