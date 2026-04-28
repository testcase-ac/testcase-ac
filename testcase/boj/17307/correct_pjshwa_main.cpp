#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2.5e5;
int A[MAX + 1];

void solve() {
  int N, C;
  cin >> N >> C;
  for (int i = 1; i <= N; i++) cin >> A[i];

  queue<int> q;
  ll rs = 0, ls = 0;
  for (int i = 1; i < N; i++) {
    int x = A[i + 1] - A[i];
    if (x < 0) x += C;
    q.push(x);
    rs += x;
  }

  ll mval = rs, midx = 1;
  for (int i = 2; i <= N; i++) {
    ll f = q.front(); q.pop();
    ls += (f == 0 ? 0 : C - f);
    rs -= f;
    ll nval = max(rs, ls);

    if (nval < mval) {
      mval = nval;
      midx = i;
    }
  }

  cout << midx << '\n' << mval << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
