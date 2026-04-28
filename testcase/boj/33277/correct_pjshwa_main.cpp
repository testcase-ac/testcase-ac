#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, M; cin >> N >> M;
  int B = M * 1440 / N;
  int HH = B / 60, MM = B % 60;
  cout << setw(2) << setfill('0') << HH << ':' << setw(2) << setfill('0') << MM << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
