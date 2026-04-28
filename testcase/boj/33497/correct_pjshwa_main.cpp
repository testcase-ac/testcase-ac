#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, M; cin >> N >> M;
  vector<string> ans(N, string(M, '+'));

  int fi = 0;
  for (int j = 0; j < M; ++j) {
    int Ai, Bi; cin >> Ai >> Bi;
    if (Ai + Bi > N) {
      cout << "NO\n";
      return;
    }

    int free = N - (Ai + Bi);
    for (int g = 0; g < free && fi < N; ++g) ans[fi++][j] = 'X';
    for (int i = 0; i < N; ++i) {
      if (ans[i][j] == 'X') continue;
      if (Ai) ans[i][j] = '+', --Ai;
      else if (Bi) ans[i][j] = '-', --Bi;
    }
    assert(Ai == 0 && Bi == 0);
  }

  if (fi < N) {
    cout << "NO\n";
    return;
  }

  cout << "YES\n";
  for (auto& s : ans) cout << s << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
