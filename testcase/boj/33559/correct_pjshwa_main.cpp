#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e5;
int A[MAXN], B[MAXN];

void solve() {
  int N, x; cin >> N;

  map<int, int> occ; int Ai = 0, Bi = 0, pcnt = 0;;
  for (int i = 0; i < N; ++i) cin >> x, ++occ[x];
  for (int i = 0; i < N; ++i) {
    cin >> x;
    if (occ[x] > 0) {
      A[Ai++] = B[Bi++] = x;
      ++pcnt;
    }
    --occ[x];
  }

  for (auto& [k, v] : occ) {
    while (v > 0) A[Ai++] = k, --v;
    while (v < 0) B[Bi++] = k, ++v;
  }
  assert(Ai == Bi && Ai == N);

  cout << pcnt << '\n';
  for (int i = 0; i < N; ++i) cout << A[i] << ' ';
  cout << '\n';
  for (int i = 0; i < N; ++i) cout << B[i] << ' ';
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
