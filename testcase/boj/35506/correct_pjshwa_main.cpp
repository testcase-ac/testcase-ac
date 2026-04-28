#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void print(char c, int t) {
  while (t--) cout << c;
}

void solve() {
  int N; cin >> N;
  for (int i = 1; i <= N; ++i) {
    print(' ', 2 * N - i);
    print('*', 1);
    print(' ', N);
    print('*', 1);
    print(' ', 2 * i - 1);
    print('*', 1);
    print(' ', N - i);
    cout << '\n';
  }
  for (int i = 1; i <= N; ++i) {
    print(' ', N - i);
    print('*', 1);
    print(' ', N + 2 * i - 1);
    print('*', 1);
    print(' ', 2 * (N - i) + 1);
    print('*', 1);
    print(' ', i - 1);
    cout << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
