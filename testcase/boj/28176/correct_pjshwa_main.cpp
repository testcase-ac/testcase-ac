#include <bits/stdc++.h> 
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e5, INF = 0x3f3f3f3f;
int A[MAX], N;

bool check(int g) {
  bool ret = true;
  for (int i = 0; i < N; i++) {
    int x = A[i];
    ret &= (A[i] % g == 0 || g * 2 < x);
  }
  return ret;
}

void solve() {
  int mmin = INF; cin >> N;
  for (int i = 0; i < N; i++) {
    cin >> A[i];
    mmin = min(mmin, A[i]);
  }

  int rmax = (mmin - 1) / 2, ans = 0;
  for (int g : {rmax, rmax + 1, mmin}) {
    if (g && check(g)) ans = max(ans, g);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
