#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

int ask(int c, int r) {
  cout << "? " << c << ' ' << r << endl;
  int res; cin >> res;
  return res;
}

void answer(int c, int r) {
  cout << "! " << c << ' ' << r << endl;
}

void solve() {
  int N; cin >> N;

  int c = ask(N, 1);
  if (c == N) return answer(N, 1);
  else answer(c, ask(N - c, 1));
}

int main() {
  // fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
