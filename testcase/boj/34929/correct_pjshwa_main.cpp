#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 3e5;
int A[MAXN];

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; ++i) cin >> A[i];
  if (N == 1) return cout << A[0] << '\n', void();

  sort(A, A + N);
  cout << A[N - 2] << '\n';

  int l = 0, r = N - 3;
  while (l < r) {
    int m = (l + r) / 2;
    cout << A[l] << ' ' << A[m] << ' ' << A[r] << '\n';
    ++l; --r;
  }
  assert(l == r);
  cout << A[l] << ' ' << A[N - 2] << ' ' << A[N - 1] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
