#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

int N;
void solve() {
  int x, cnt = 0;
  for (int i = 0; i < N; ++i) {
    cin >> x;
    if (x == 1) ++cnt;
  }

  cout << "Mary won " << N - cnt << " times and John won " << cnt << " times\n";
}

int main() {
  fast_io();

  while (cin >> N) {
    if (N == 0) break;
    solve();
  }
}
