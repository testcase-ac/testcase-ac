#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 100;
bool a[MAX];

void solve() {
  int N, Y;
  cin >> N >> Y;
  for (int i = 0; i < Y; i++) {
    int x;
    cin >> x;
    a[x] = 1;
  }

  int ans = 0;
  for (int i = 0; i < N; i++) {
    if (a[i]) ans++;
    else cout << i << '\n';
  }
  cout << "Mario got " << ans << " of the dangerous obstacles.\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
