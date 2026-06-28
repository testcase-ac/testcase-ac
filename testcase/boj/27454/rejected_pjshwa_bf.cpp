#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e6;
ll A[MAXN + 1], P[MAXN + 1];

void solve() {
  int N, K, Y; cin >> N >> K >> Y; --K;
  for (int i = 1; i <= N; ++i) cin >> A[i];
  sort(A + 1, A + N + 1);
  for (int i = 1; i <= N; ++i) P[i] = P[i - 1] + A[i];

  ll ans = 1e18;
  for (int i = 1; i <= N - K + 1; ++i) {
    vector<int> P;
    for (int j = 1; j <= K; ++j) P.push_back(A[i + j - 1]);
    P.push_back(Y);
    sort(P.begin(), P.end());

    ll med = P[K / 2], sum = 0;
    for (int e : P) sum += abs(e - med);
    ans = min(ans, sum);
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
