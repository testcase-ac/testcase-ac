#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  string A, T; cin >> A >> T;
  int N = T.size(), M = A.size();
  int lp = 0, rp = N - 1;

  string L, R, B = A;
  reverse(B.begin(), B.end());
  while (lp <= rp) {
    while (lp <= rp) {
      L.push_back(T[lp++]);
      if (L.size() >= M && L.substr(L.size() - M) == A) {
        L.resize(L.size() - M);
        break;
      }
    }

    while (lp <= rp) {
      R.push_back(T[rp--]);
      if (R.size() >= M && R.substr(R.size() - M) == B) {
        R.resize(R.size() - M);
        break;
      }
    }
  }

  reverse(R.begin(), R.end());
  L += R;

  // Take one last pass
  string ans;
  for (char& c : L) {
    ans.push_back(c);
    if (ans.size() >= M && ans.substr(ans.size() - M) == A) {
      ans.resize(ans.size() - M);
    }
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
