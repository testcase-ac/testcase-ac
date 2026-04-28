#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

int tc;
void solve() {
  cout << "Data Set " << ++tc << ":\n";
  int n, c, l; cin >> n >> c >> l;

  queue<int> Q[l + 1], R[l + 1];
  vector<int> C[l + 1];
  for (int i = 0; i < n; i++) {
    int x; string o; cin >> x >> o;
    if (o == "S") R[x].push(i);
    else Q[x].push(i);
  }
  for (int i = 0; i < c; i++) {
    int x, cap; cin >> x >> cap;
    C[x].push_back(cap);
  }

  int ans = n;
  for (int i = 1; i <= l; i++) {
    sort(C[i].begin(), C[i].end());
    while (!C[i].empty()) {
      int cap = C[i].back(); C[i].pop_back();
      if (R[i].empty()) continue;

      R[i].pop();
      int use = 1;
      while (use < cap) {
        if (Q[i].empty() && R[i].empty()) break;

        if (!Q[i].empty()) Q[i].pop(), use++;
        else if (!R[i].empty()) R[i].pop(), use++;
      }
      ans -= use;
    }
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
