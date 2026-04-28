#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N;
  if (N < 6) cout << "-1\n";
  else {
    int h = N / 2;
    if (N & 1) {
      cout << "4\n";
      cout << "1 " << h << ' ' << h + 1 << ' ' << N - 2 << '\n';
    } else {
      cout << "3\n";
      cout << "1 " << h << ' ' << h + 1 << '\n';
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
