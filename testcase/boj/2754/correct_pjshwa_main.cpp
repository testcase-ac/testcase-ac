#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  string S;
  cin >> S;

  string res;
  if (S == "A+") res = "4.3";
  if (S == "A0") res = "4.0";
  if (S == "A-") res = "3.7";
  if (S == "B+") res = "3.3";
  if (S == "B0") res = "3.0";
  if (S == "B-") res = "2.7";
  if (S == "C+") res = "2.3";
  if (S == "C0") res = "2.0";
  if (S == "C-") res = "1.7";
  if (S == "D+") res = "1.3";
  if (S == "D0") res = "1.0";
  if (S == "D-") res = "0.7";
  if (S == "F") res = "0.0";

  cout << res << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
