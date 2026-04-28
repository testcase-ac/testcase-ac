#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; string S; cin >> N >> S;
  if (N == 1) return cout << "NO\n", void();

  vector<int> A; int last = -1, str = 0;
  for (int i = 0; i < N; ++i) {
    if (S[i] == last) ++str;
    else {
      if (str) A.push_back(str);
      str = 1; last = S[i];
    }
  }
  if (str) A.push_back(str);

  int Z = A.size(), ok = A[0] == 1 || A.back() == 1;
  for (int i = 1; i < Z - 1; ++i) ok |= A[i] == 2;

  if (ok) cout << "YES\n";
  else cout << "NO\n";
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
