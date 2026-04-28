#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, M; string S, T;
  cin >> N >> M >> S >> T;

  vector<int> sp, tp;
  for (int i = 0; i < N + M; ++i) {
    if (S[i] == '1') sp.push_back(i);
    if (T[i] == '1') tp.push_back(i);
  }

  ll ssum = 0, tsum = 0;
  for (int i = 0; i < M; i++) {
    ll diff = abs(sp[i] - tp[i]);
    if (diff & 1) {
      if (ssum > tsum) ssum += diff / 2, tsum += diff - diff / 2;
      else tsum += diff / 2, ssum += diff - diff / 2;
    }
    else ssum += diff / 2, tsum += diff / 2;
  }
  cout << ssum * ssum + tsum * tsum << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
