#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1000;
int A[MAXN], B[MAXN], V[MAXN];

int tc;
void solve() {
  cout << "Case #" << ++tc << ": ";

  int N; cin >> N;
  for (int i = 0; i < N; ++i) {
    cin >> A[i] >> B[i];
    V[i] = 0;
  }

  int ans = 0, val = 0;
  auto inc1 = [&](int i) {
    V[i] += 1; val += 1; ans += 1;
  };
  auto inc2 = [&](int i) {
    val += 2 - V[i]; ans += 1;
    V[i] = 2;
  };

  while (val < 2 * N) {
    int f = 0;
    for (int i = 0; i < N; ++i) {
      if (V[i] != 2 && B[i] <= val) {
        f = 1; inc2(i);
        break;
      }
    }
    if (f == 1) continue;

    int maxb = -1;
    for (int i = 0; i < N; ++i) {
      if (V[i] == 0 && A[i] <= val) {
        if (B[i] > maxb) maxb = B[i];
      }
    }
    if (maxb == -1) return cout << "Too Bad\n", void();

    for (int i = 0; i < N; ++i) {
      if (V[i] == 0 && A[i] <= val && B[i] == maxb) {
        inc1(i);
        break;
      }
    }
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
