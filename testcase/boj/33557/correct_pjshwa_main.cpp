#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  ll A, B; cin >> A >> B;
  string Astr = to_string(A), Bstr = to_string(B);
  while (Astr.size() < Bstr.size()) Astr = '.' + Astr;
  while (Bstr.size() < Astr.size()) Bstr = '.' + Bstr;

  string res = "";
  for (int i = 0; i < (int)Astr.size(); ++i) {
    int a = Astr[i] == '.' ? 1 : Astr[i] - '0';
    int b = Bstr[i] == '.' ? 1 : Bstr[i] - '0';
    res += to_string(a * b);
  }
  cout << (res == to_string(A * B)) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
