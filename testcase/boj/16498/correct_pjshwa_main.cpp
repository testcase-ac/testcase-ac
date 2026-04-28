#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int INF = 1e9 + 7;

void solve() {
  int A, B, C;
  cin >> A >> B >> C;

  vector<int> va, vb, vc;
  for (int i = 1; i <= A; i++) {
    int x;
    cin >> x;
    va.push_back(x);
  }
  for (int i = 1; i <= B; i++) {
    int x;
    cin >> x;
    vb.push_back(x);
  }
  for (int i = 1; i <= C; i++) {
    int x;
    cin >> x;
    vc.push_back(x);
  }
  sort(va.begin(), va.end());
  sort(vb.begin(), vb.end());
  sort(vc.begin(), vc.end());

  int ans = INF;
  for (int a : va) for (int b : vb) {
    int mx = max(a, b), mm = min(a, b);
    auto it = lower_bound(vc.begin(), vc.end(), mm);
    if (it == vc.end()) it--;

    int mc = *it;
    mx = max(mx, mc);
    mm = min(mm, mc);
    ans = min(ans, mx - mm);
  }
  for (int a : va) for (int c : vc) {
    int mx = max(a, c), mm = min(a, c);
    auto it = lower_bound(vb.begin(), vb.end(), mm);
    if (it == vb.end()) it--;
    int mc = *it;
    mx = max(mx, mc);
    mm = min(mm, mc);
    ans = min(ans, mx - mm);
  }
  for (int b : vb) for (int c : vc) {
    int mx = max(b, c), mm = min(b, c);
    auto it = lower_bound(va.begin(), va.end(), mm);
    if (it == va.end()) it--;
    int mc = *it;
    mx = max(mx, mc);
    mm = min(mm, mc);
    ans = min(ans, mx - mm);
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
