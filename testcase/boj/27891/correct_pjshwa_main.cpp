#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  string C[4] = {"northlondo", "branksomeh", "koreainter", "stjohnsbur"};
  string A[4] = {"NLCS", "BHA", "KIS", "SJA"};

  string S; cin >> S;
  for (int k = 0;; k++) {
    for (int i = 0; i < 4; i++) {
      if (S == C[i]) return cout << A[i] << '\n', []{}();
    }

    for (int j = 0; j < 10; j++) {
      S[j]++;
      if (S[j] == 'z' + 1) S[j] = 'a';
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
