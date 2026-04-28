#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int M; cin >> M;
  map<string, int> T;
  while (M--) {
    string S; int x; cin >> S >> x;
    T[S] += x;
  }

  int N = T.size();
  vector<int> A;
  for (auto& [_, x] : T) A.push_back(x);

  for (int i = 0; i < N; i++) for (int j = i + 1; j < N; j++) {
    int mmin = min(A[i], A[j]), mmax = max(A[i], A[j]);

    if (mmin * 1618 / 1000 == mmax) return cout << "Delicious!\n", void();
  }
  cout << "Not Delicious...\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
