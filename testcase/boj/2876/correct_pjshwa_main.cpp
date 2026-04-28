#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e5;
int A[MAX], B[MAX], d[MAX][2];

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; i++) cin >> A[i] >> B[i];

  int mstreak = 1, mgrade = min(A[0], B[0]);

  d[0][0] = d[0][1] = 1;
  for (int i = 1; i < N; i++) {
    d[i][0] = d[i][1] = 1;

    if (A[i] == A[i - 1]) d[i][0] = max(d[i][0], d[i - 1][0] + 1);
    if (B[i] == B[i - 1]) d[i][1] = max(d[i][1], d[i - 1][1] + 1);
    if (A[i] == B[i - 1]) d[i][0] = max(d[i][0], d[i - 1][1] + 1);
    if (B[i] == A[i - 1]) d[i][1] = max(d[i][1], d[i - 1][0] + 1);

    if (d[i][0] > mstreak) mstreak = d[i][0], mgrade = A[i];
    else if (d[i][0] == mstreak && A[i] < mgrade) mgrade = A[i];

    if (d[i][1] > mstreak) mstreak = d[i][1], mgrade = B[i];
    else if (d[i][1] == mstreak && B[i] < mgrade) mgrade = B[i];
  }

  cout << mstreak << ' ' << mgrade << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
