#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 30;
int a[MAX + 1];

void solve() {
  int n;
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> a[i];

  vector<int> ans;
  for (int f = n; f >= 3; f--) {
    for (int i = 1; i <= f; i++) {
      if (a[i] == f) {
        ans.push_back(i);
        ans.push_back(f);
        reverse(a + 1, a + i + 1);
        reverse(a + 1, a + f + 1);
        break;
      }
    }
  }
  if (a[1] == 2) ans.push_back(2);

  cout << ans.size() << ' ';
  for (int e : ans) cout << e << ' ';
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
