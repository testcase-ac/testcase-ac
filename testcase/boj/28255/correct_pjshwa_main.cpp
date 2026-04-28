#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

string rev(string S) {
  reverse(S.begin(), S.end());
  return S;
}

string tail(string S) {
  return S.substr(1);
}

void solve() {
  string S; cin >> S;
  int N = S.size();
  string Sp = S.substr(0, (N - 1) / 3 + 1);

  if (S == Sp + rev(Sp) + Sp) return cout << "1\n", void();
  if (S == Sp + tail(rev(Sp)) + Sp) return cout << "1\n", void();
  if (S == Sp + rev(Sp) + tail(Sp)) return cout << "1\n", void();
  if (S == Sp + tail(rev(Sp)) + tail(Sp)) return cout << "1\n", void();
  cout << "0\n";
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
