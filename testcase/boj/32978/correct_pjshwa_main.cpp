#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N;
  vector<string> A(N);
  set<string> B;
  for (int i = 0; i < N; ++i) cin >> A[i];
  for (int i = 0; i < N - 1; ++i) {
    string S; cin >> S;
    B.insert(S);
  }

  for (string& s : A) {
    if (B.find(s) == B.end()) {
      cout << s << '\n';
      return;
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
