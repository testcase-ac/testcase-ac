#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  set<string> U{"ChongChong"};

  int N;
  cin >> N;
  for (int i = 1; i <= N; i++) {
    string A, B;
    cin >> A >> B;
    if (U.count(A) || U.count(B)) U.insert(A), U.insert(B);
  }

  cout << U.size() << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
