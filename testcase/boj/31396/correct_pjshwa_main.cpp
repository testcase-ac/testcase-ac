#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 2e5;
int A[MAXN], D[MAXN];

void solve() {
  int N, K, M; cin >> N >> K >> M;
  for (int i = 0; i < N; ++i) cin >> A[i];
  sort(A, A + N, greater<int>());

  for (int i = 0; i < M; ++i) cin >> D[i];
  sort(D, D + M, greater<int>());

  int l = 1, r = M + 1;
  while (l < r) {
    int mid = (l + r) / 2;

    priority_queue<int, vector<int>, greater<int>> pq;
    for (int i = 0; i < mid; ++i) pq.push(D[i]);

    ll avail = K;
    bool ok = true; int j = 0;
    for (int lev = 0; lev <= MAXN; ++lev) {
      while (!pq.empty() && pq.top() == lev) {
        pq.pop(); --avail;
      }
      if (avail < 0) {
        ok = false;
        break;
      }
      if (pq.empty()) break;
      if (avail == 0) {
        ok = false;
        break;
      }

      ll navail = avail;
      while (j < N && avail--) navail += A[j++] - 1;
      avail = navail;
    }

    if (ok) l = mid + 1;
    else r = mid;
  }

  cout << l - 1 << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
