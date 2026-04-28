#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using matrix = vector<vector<ll>>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 5000;
int C[MAXN];

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; ++i) cin >> C[i];

  string S, T; cin >> S >> T;
  vector<int> L, R, D;
  for (int i = 0; i < N; ++i) {
    if (S[i] == '1' && T[i] == '0') L.push_back(C[i]);
    if (S[i] == '1' && T[i] == '1') D.push_back(C[i]);
    if (S[i] == '0' && T[i] == '1') R.push_back(C[i]);
  }
  sort(L.begin(), L.end(), greater<int>());
  sort(D.begin(), D.end(), greater<int>());
  sort(R.begin(), R.end());

  ll cur = 0, acc = 0;
  for (int i = 0; i < N; ++i) if (S[i] == '1') acc += C[i];
  for (int e : L) acc -= e, cur += acc;
  for (int e : R) acc += e, cur += acc;

  ll lsum = 0, rsum = 0, dsum = 0;
  for (int e : L) lsum += e;
  for (int e : R) rsum += e;
  for (int e : D) dsum += e;

  int lN = L.size(), rN = R.size();
  int li = 0, ri = rN - 1;

  ll ans = cur;
  for (int e : D) {
    dsum -= e;

    while (li < lN && L[li] >= e) lsum -= L[li++];
    while (ri >= 0 && R[ri] >= e) rsum -= R[ri--];

    ll olen = lN + rN - li - (rN - ri - 1);
    ll ov = olen * e;

    ll tv = lsum + rsum + 2 * dsum + e;

    cur += tv - ov;
    ans = min(ans, cur);
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
