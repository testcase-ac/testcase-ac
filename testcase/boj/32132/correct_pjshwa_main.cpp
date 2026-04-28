#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; string S; cin >> N >> S;

  string NS = "";
  for (int i = 0; i < N; ++i) {
    char c = S[i];
    NS.push_back(c);

    while (NS.size() >= 3) {
      int Z = NS.size();
      if (NS[Z - 3] == 'P' && NS[Z - 2] == 'S' && (NS[Z - 1] == '4' || NS[Z - 1] == '5')) NS.pop_back();
      else break;
    }
  }

  cout << NS << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
