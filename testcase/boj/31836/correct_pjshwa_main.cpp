#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N;

  vector<int> A, B;
  if (N % 3 == 0) {
    for (int i = 1; i <= N; ++i) {
      if (i % 3 == 0) B.push_back(i);
      else A.push_back(i);
    }
  }
  else if (N % 3 == 1) {
    for (int i = 1; i <= N - 1; ++i) {
      if (i % 3 == 0) B.push_back(i);
      else A.push_back(i);
    }
  }
  else {
    A.push_back(1); B.push_back(2);
    for (int i = 3; i <= N; ++i) {
      if (i % 3 == 2) B.push_back(i);
      else A.push_back(i);
    }
  }

  cout << A.size() << '\n';
  for (int e : A) cout << e << ' '; cout << '\n';
  cout << B.size() << '\n';
  for (int e : B) cout << e << ' '; cout << '\n';
  
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
