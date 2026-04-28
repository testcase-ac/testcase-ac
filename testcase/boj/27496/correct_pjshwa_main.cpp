#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e6;
int A[MAX];

void solve() {
  int N, L; cin >> N >> L;

  int acc = 0, ans = 0;
  for (int i = 0; i < N; i++) {
    cin >> A[i];
    acc += A[i];
    if (i >= L) acc -= A[i - L];

    if (129 <= acc && acc <= 138) ans++;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
