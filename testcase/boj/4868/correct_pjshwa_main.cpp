#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  vector<string> A, O; string S;
  while (cin >> S) {
    A.push_back(S);

    string T = S; sort(T.begin(), T.end());
    O.push_back(T);
  }
  sort(O.begin(), O.end(), [&](string& a, string& b) {
    return a.size() < b.size();
  });

  map<string, int> dp; string mstr; int mlen = 0;
  for (auto& T : O) {
    int z = T.size();
    for (int i = 0; i < z; i++) {
      string U = T.substr(0, i) + T.substr(i + 1);
      dp[T] = max(dp[T], dp[U] + 1);
    }

    if (dp[T] > mlen) mlen = dp[T], mstr = T;
  }

  vector<string> C;
  function<void(string)> trace = [&](string T) {
    if (dp[T] == 1) return void(C.push_back(T));

    int z = T.size();
    for (int i = 0; i < z; i++) {
      string U = T.substr(0, i) + T.substr(i + 1);
      if (dp[U] + 1 == dp[T]) {
        trace(U), C.push_back(T);
        return;
      }
    }
  };

  trace(mstr);
  for (auto& T : C) {
    for (auto S : A) {
      string U = S; sort(U.begin(), U.end());
      if (T == U) {
        cout << S << '\n';
        break;
      }
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
