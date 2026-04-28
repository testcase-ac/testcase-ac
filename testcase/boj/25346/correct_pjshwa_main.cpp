#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int N;
  cin >> N;

  set<int> s;
  for (int i = 0; i < N; i++) {
    int x;
    cin >> x;
    s.insert(x);
  }

  if (s.size() == 1) {
    if (*s.begin() == 0) cout << "1\n";
    else cout << "0\n";
  }
  else {
    int mex = 0;
    for (int x : s) {
      if (x == mex) mex++;
      else break;
    }

    if (mex == 0) cout << "0\n";
    else cout << mex + 2 << '\n';
  }

}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
