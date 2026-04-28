#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 5e5;
int A[MAXN];

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; ++i) cin >> A[i];
  sort(A, A + N);

  multiset<int> S;
  for (int i = 1; i < N; ++i) {
    int j = N - i;
    if (i < j) S.insert(A[i] + A[j]);
    else break;
  }

  int ans = *S.rbegin() - *S.begin();
  for (int i = 1; i < N; ++i) {
    int j = 2 * i < N ? N - i : N - i - 1;
    S.erase(S.find(A[i] + A[j]));
    S.insert(A[i - 1] + A[j]);
    ans = min(ans, *S.rbegin() - *S.begin());
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
