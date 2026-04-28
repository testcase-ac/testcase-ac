#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int n, k;
  cin >> n >> k;
  for (int i = 0; i < k; i++) {
    int qi;
    cin >> qi;

    vector<int> u(qi);
    for (int j = 0; j < qi; j++) cin >> u[j];
    sort(u.begin(), u.end());

    for (int j = 0; j < qi; j++) {
      cout << u[j] + j + 1 << " ";
    }
    cout << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
