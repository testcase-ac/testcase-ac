#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1000;
int A[MAX];

void solve() {
  int N, M; cin >> N >> M;
  for (int i = 0; i < N; i++) cin >> A[i];
  sort(A, A + N, [](int a, int b) {
    bool adiv = a % 10 == 0, bdiv = b % 10 == 0;
    if (adiv != bdiv) return adiv;
    return a < b;
  });

  int ans = 0;
  for (int i = 0; i < N; i++) {
    if (A[i] < 10) continue;

    while (M && A[i] > 10) {
      M--; A[i] -= 10;
      ans++;
    }
    ans += A[i] == 10;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
