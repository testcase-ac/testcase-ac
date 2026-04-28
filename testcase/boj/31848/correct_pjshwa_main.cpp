#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e5;
int A[MAXN];

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; ++i) cin >> A[i], A[i] += i;

  vector<pii> holes;
  for (int i = 0; i < N; ++i) {
    if (holes.empty() || holes.back().first < A[i]) {
      holes.emplace_back(A[i], i + 1);
    }
  }

  int Q; cin >> Q;
  while (Q--) {
    int x; cin >> x;
    auto it = lower_bound(holes.begin(), holes.end(), pii(x, 0));
    cout << it->second << ' ';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
