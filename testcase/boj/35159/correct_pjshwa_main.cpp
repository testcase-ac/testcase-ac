#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  string S, T; cin >> S;
  ll ki = 0, ans = 0;
  for (int i = 0; i < (int)S.size(); ++i) {
    if (S[i] == 'K') ans += i - ki++;
    else T.push_back(S[i]);
  }

  int N = T.size();
  int si = 0, ei = N - 1;
  while (T[si] == 'P') ++si;
  while (T[ei] == 'P') --ei;
  assert(si != ei);
  if (si != 0) {
    swap(T[si], T[0]);
    ans += si;
  }
  if (ei != N - 1) {
    swap(T[ei], T.back());
    ans += (N - 1 - ei);
  }

  vector<int> P; int pi = 0;
  for (int i = 0; i < N; ++i) {
    if (T[i] == 'P') P.push_back(i - pi++);
  }
  int Z = P.size();
  for (int i = 0; i < Z; ++i) {
    ans += abs(P[i] - P[Z / 2]);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
