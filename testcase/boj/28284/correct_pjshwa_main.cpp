#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 5e5;
ll A[MAX + 1];
ll PL[MAX + 1], PH[MAX + 1];

void solve() {
  int N, M; cin >> N >> M;
  for (int i = 1; i <= N; i++) cin >> A[i];

  sort(A + 1, A + N + 1);
  for (int i = 1; i <= N; i++) PL[i] = PL[i - 1] + A[i];
  sort(A + 1, A + N + 1, greater<int>());
  for (int i = 1; i <= N; i++) PH[i] = PH[i - 1] + A[i];

  map<int, int> dt;
  while (M--) {
    int Si, Ei; cin >> Si >> Ei;
    dt[Si]++; dt[Ei + 1]--;
  }

  ll Lx = 0, Lp = 0, ans1 = 0, ans2 = 0;
  for (auto [x, d] : dt) {
    ll pd = x - Lx;
    ans1 += PL[Lp] * pd;
    ans2 += PH[Lp] * pd;

    Lx = x; Lp += d;
  }
  cout << ans1 << ' ' << ans2 << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
