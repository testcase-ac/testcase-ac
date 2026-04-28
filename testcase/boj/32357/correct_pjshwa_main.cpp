#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

bool is_palindrome(string& s) {
  int n = s.size();
  for (int i = 0; i < n / 2; i++) {
    if (s[i] != s[n - i - 1]) return false;
  }
  return true;
}

void solve() {
  int N, cnt = 0; cin >> N;
  for (int i = 0; i < N; ++i) {
    string S; cin >> S;
    cnt += is_palindrome(S);
  }
  cout << cnt * (cnt - 1) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
