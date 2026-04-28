#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; string S; int D, M; cin >> N >> S >> D >> M;

  vector<int> streaks; int cur = 0;
  map<char, int> tal;
  for (int i = 0; i < N; ++i) {
    if (S[i] == 'H' || S[i] == 'Y' || S[i] == 'U') {
      streaks.push_back(cur);
      ++tal[S[i]];
      cur = 0;
    }
    else ++cur;
  }
  streaks.push_back(cur);

  int cost = 0;
  for (int s : streaks) cost += min(D + M, s * D);
  int freq = min({tal['H'], tal['Y'], tal['U']});

  if (cost == 0) cout << "Nalmeok\n";
  else cout << cost << '\n';

  if (freq == 0) cout << "I love HanYang University\n";
  else cout << freq << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
