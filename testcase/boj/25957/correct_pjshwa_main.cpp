#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N;
  cin >> N;

  map<tuple<char, char, string, int>, string> t;
  for (int i = 0; i < N; i++) {
    string U, O;
    cin >> U;
    O = U;

    tuple<char, char, string, int> key = {U[0], U[U.size() - 1], U.substr(1, U.size() - 2), U.size()};
    sort(get<2>(key).begin(), get<2>(key).end());
    t[key] = O;
  }

  int Q;
  cin >> Q;
  while (Q--) {
    string S;
    cin >> S;

    tuple<char, char, string, int> key = {S[0], S[S.size() - 1], S.substr(1, S.size() - 2), S.size()};
    sort(get<2>(key).begin(), get<2>(key).end());
    cout << t[key] << ' ';
  }
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
