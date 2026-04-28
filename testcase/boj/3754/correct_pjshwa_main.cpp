#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N;

  bool flag = 1; int x, sum = 0;
  for (int i = 0; i < N; ++i) {
    cin >> x; flag &= (x == 1);
    sum ^= x;
  }
  if (flag) flag = sum != 1;
  else flag = sum != 0;
  if (flag) cout << "John\n";
  else cout << "Brother\n";
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
