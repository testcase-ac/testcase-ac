#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 2e5, INF = 0x3f3f3f3f;
string S[MAXN];

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; ++i) cin >> S[i];
  sort(S, S + N);

  int maxk = INF;
  for (int i = 0; i < N; i += 2) {
    int l = 0;
    while (l < S[i].size() && S[i][l] == S[i + 1][l]) ++l;
    maxk = min(maxk, l);
  }
  cout << maxk << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
