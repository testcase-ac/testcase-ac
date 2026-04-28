#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  string S; cin >> S;
  int N = S.size();

  cout << S[0];
  for (int i = 1; i < N; ++i) {
    if (S[i] == '(' && S[i - 1] == ')') cout << '+';
    if (S[i] == ')' && S[i - 1] == '(') cout << '1';
    cout << S[i];
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
