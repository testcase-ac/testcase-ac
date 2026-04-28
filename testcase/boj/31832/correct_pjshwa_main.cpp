#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

bool upper_more_than_lower(string &S) {
  int lower = 0, upper = 0;
  for (char c : S) {
    if (islower(c)) ++lower;
    else if (isupper(c)) ++upper;
  }
  return upper > lower;
}

bool is_all_digits(string &S) {
  for (char c : S) {
    if (!isdigit(c)) return false;
  }
  return true;
}

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; ++i) {
    string S; cin >> S;
    if (S.size() > 10) continue;
    if (is_all_digits(S)) continue;
    if (upper_more_than_lower(S)) continue;
    cout << S << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
