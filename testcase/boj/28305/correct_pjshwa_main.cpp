#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 2e5;
int A[MAX];

void solve() {
  int N, T; cin >> N >> T;
  for (int i = 0; i < N; i++) cin >> A[i];
  sort(A, A + N);

  int l = 1, r = N + 1;
  while (l < r) {
    int m = (l + r) / 2;

    queue<int> Q; int f = 1;
    for (int i = 0; i < N; i++) {
      int mS = max(1, A[i] - T + 1), mE = mS + T - 1;
      while (!Q.empty() && Q.front() < mS) Q.pop();

      if (Q.size() < m) Q.push(mE);
      else if (Q.front() >= mE) { f = 0; break; }
      else {
        int nS = Q.front() + 1; Q.pop();
        Q.push(nS + T - 1);
      }
    }

    if (f) r = m;
    else l = m + 1;
  }

  cout << l << '\n';
  // {
  //   queue<int> Q;
  //   for (int i = 0; i < N; i++) {
  //     int mS = A[i] - T + 1;
  //     while (!Q.empty() && Q.front() < mS) Q.pop();

  //     if (Q.size() < l) Q.push(A[i]), cout << A[i] << ' ';
  //     else if (Q.front() >= A[i]) { break; }
  //     else {
  //       int nS = Q.front() + 1; Q.pop();
  //       Q.push(nS + T - 1), cout << nS + T - 1 << ' ';
  //     }
  //   }
  // }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
