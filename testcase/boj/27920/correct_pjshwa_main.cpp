#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N;

  deque<int> T;
  for (int i = 1; i <= N; i++) {
    if (i & 1) T.push_back(i);
    else T.push_front(i);
  }

  cout << "YES\n";
  map<int, int> inv;
  for (int i = 0; i < N; i++) {
    cout << T[i] << " \n"[i == N - 1];
    inv[T[i]] = i + 1;
  }
  for (int i = 1; i <= N; i++) {
    cout << inv[i] << " \n"[i == N];
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
