#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 50000;
int A[MAXN];

int tc;
void solve() {
  cout << "Case " << ++tc << ": ";

  int N, W; cin >> N >> W;
  for (int i = 0; i < N; ++i) cin >> A[i];

  int Q; cin >> Q;
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
