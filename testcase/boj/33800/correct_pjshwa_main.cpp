#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int n; cin >> n;

  vector<string> C;
  while (n) {
    int q1 = sqrt(n), q2 = sqrt(n / 2);
    int x1 = q1 * q1, x2 = q2 * q2 * 2;
    int x; string V;
    if (x1 > x2) x = x1, V = "A" + to_string(q1);
    else x = x2, V = "B" + to_string(q2);

    C.emplace_back(V);
    n -= x;
  }
  assert(n == 0);

  cout << C.size() << ' ';
  for (auto& s : C) cout << s << ' ';
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
