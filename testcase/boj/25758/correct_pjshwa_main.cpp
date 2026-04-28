#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 26 * 26;
int d[MAX];

int c2v(string c) {
  char c1 = c[0], c2 = c[1];
  return (c1 - 'A') * 26 + (c2 - 'A');
}

void solve() {
  int N;
  cin >> N;

  for (int i = 0; i < N; i++) {
    string c;
    cin >> c;
    int v = c2v(c);
    d[v]++;
  }

  set<int> ans;
  for (int p1 = 0; p1 < MAX; p1++) for (int p2 = 0; p2 < MAX; p2++) {
    if (p1 == p2 && d[p1] < 2) continue;
    if (d[p1] == 0 || d[p2] == 0) continue;
    ans.insert(max(p1 / 26, p2 % 26));
  }

  cout << ans.size() << '\n';
  for (int e : ans) cout << (char)('A' + e) << ' ';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
