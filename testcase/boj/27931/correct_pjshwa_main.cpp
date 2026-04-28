#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const ll INF = 1e18;

void solve() {
  int N; cin >> N;
  vector<ll> A(N);
  for (int i = 0; i < N; i++) cin >> A[i];
  sort(A.begin(), A.end());

  ll o_last = INF, e_last = INF, o_ans = INF, e_ans = INF;
  for (int i = 0; i < N; i++) {
    ll o_dis = INF, e_dis = INF;
    if (o_last != INF) {
      o_dis = A[i] - o_last;
      if (o_dis & 1) o_ans = min(o_ans, o_dis);
      else e_ans = min(e_ans, o_dis);
    }
    if (e_last != INF) {
      e_dis = A[i] - e_last;
      if (e_dis & 1) o_ans = min(o_ans, e_dis);
      else e_ans = min(e_ans, e_dis);
    }

    if (A[i] & 1) o_last = A[i];
    else e_last = A[i];
  }

  if (o_ans == INF) o_ans = -1;
  if (e_ans == INF) e_ans = -1;
  cout << e_ans << ' ' << o_ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
