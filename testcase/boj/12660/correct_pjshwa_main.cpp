#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const string P = "welcome to code jam";
const int MOD = 1e4;
map<char, vector<int>> pp;

int tc;
void solve() {
  cout << "Case #" << ++tc << ": ";

  string S; getline(cin, S);
  int d[20]{}; d[0] = 1;
  for (char c : S) for (int i : pp[c]) {
    d[i] = (d[i] + d[i - 1]) % MOD;
  }
  cout << setw(4) << setfill('0') << d[19] << '\n';
}

int main() {
  fast_io();

  for (int i = 0; i < P.size(); i++) {
    if (pp.count(P[i])) pp[P[i]].push_back(i + 1);
    else pp[P[i]] = {i + 1};
  }

  int t = 1;
  cin >> t; cin.ignore();
  while (t--) solve();
}
