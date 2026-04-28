#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
int a[MAX];

bool beats(int p, int o) {
  return p == o + 1 || (p == 0 && o == 2);
}

void solve() {
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    string s;
    cin >> s;
    if (s == "H") a[i] = 0;
    if (s == "P") a[i] = 1;
    if (s == "S") a[i] = 2;
  }

  int ans = 0;
  for (int p : {0, 1, 2}) for (int e : {0, 1, 2}) {
    if (p == e) continue;

    int cnt = 0;
    for (int i = 0; i < n; i++) if (beats(e, a[i])) cnt++;
    ans = max(ans, cnt);

    for (int i = 0; i < n; i++) {
      if (beats(e, a[i])) cnt--;
      if (beats(p, a[i])) cnt++;
      ans = max(ans, cnt);
    }
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
