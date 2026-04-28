#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; string S; cin >> N >> S;

  vector<int> Ps, Cs;
  for (int i = 0; i < N; ++i) {
    if (S[i] == 'P') Ps.push_back(i);
    if (S[i] == 'C') Cs.push_back(i);
  }

  int Z = min(Ps.size(), Cs.size());
  for (int i = 0; i < Z; ++i) {
    swap(S[Ps[i]], S[Cs[i]]);
  }
  cout << S << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
