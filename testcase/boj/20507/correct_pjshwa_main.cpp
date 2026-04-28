#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N;

  vector<int> A(N), B(N);
  for (int i = 0; i < N; i++) cin >> A[i], B[i] = A[i];
  sort(B.begin(), B.end(), greater<>());

  vector<string> ops;
  for (int i = 0; i < N; i++) {
    bool f = true; vector<int> NA;

    // Put all books except the biggest, on the right shelf
    // Hold the biggest book in left hand
    for (int j = 0; j < N - i; j++) {
      if (f && A[j] == B[i]) {
        ops.push_back("UZMI L L");
        f = false;
      }
      else {
        ops.push_back("UZMI D L");
        ops.push_back("STAVI D D");
        NA.push_back(A[j]);
      }
    }

    // Put the biggest book on the left shelf
    ops.push_back("STAVI L L");

    // Move all books on the right shelf to the left shelf
    for (int j = 0; j < N - i - 1; j++) {
      ops.push_back("UZMI D D");
      ops.push_back("STAVI D L");
    }
    A = NA;
  }

  cout << ops.size() << '\n';
  for (auto& op : ops) cout << op << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
