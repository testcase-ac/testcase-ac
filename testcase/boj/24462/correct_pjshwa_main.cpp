#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

ll lcm(ll a, ll b) {
  return a / __gcd(a, b) * b;
}

void solve() {
  int N, D;
  cin >> N >> D;

  vector<pll> A(N);
  for (auto& [t, k] : A) cin >> t >> k;

  ll max_call = 0;
  for (int i = 0; i < N; i++) for (int j = i + 1; j < N; j++) {
    auto [at, ak] = A[i];
    auto [bt, bk] = A[j];

    ll cur_call = D / ak + 1 + D / bk + 1;
    cur_call -= D / lcm(ak, bk) + 1;

    if (at > 0) {
      if (bt == 0) {
        at -= ak;
        cur_call -= at / ak + 1;

        int T = at;
        cur_call += T / lcm(ak, bk) + 1;
      }
      else {
        at -= ak; bt -= bk;
        cur_call -= at / ak + 1 + bt / bk + 1;
        cur_call += max(at, bt) / lcm(ak, bk) + 1;
      }
    }
    else if (bt > 0) {
      bt -= bk;
      cur_call -= bt / bk + 1;

      int T = bt;
      cur_call += T / lcm(ak, bk) + 1;
    }

    max_call = max(max_call, cur_call);
  }

  for (int i = 0; i < N; i++) for (int j = i + 1; j < N; j++) {
    auto [at, ak] = A[i];
    auto [bt, bk] = A[j];

    ll cur_call = D / ak + 1 + D / bk + 1;
    cur_call -= D / lcm(ak, bk) + 1;

    if (at > 0) {
      if (bt == 0) {
        at -= ak;
        cur_call -= at / ak + 1;

        int T = at;
        cur_call += T / lcm(ak, bk) + 1;
      }
      else {
        at -= ak; bt -= bk;
        cur_call -= at / ak + 1 + bt / bk + 1;
        cur_call += max(at, bt) / lcm(ak, bk) + 1;
      }
    }
    else if (bt > 0) {
      bt -= bk;
      cur_call -= bt / bk + 1;

      int T = bt;
      cur_call += T / lcm(ak, bk) + 1;
    }

    if (cur_call == max_call) {
      cout << i + 1 << ' ' << j + 1 << '\n';
      cout << max_call << '\n';
      return;
    }

  }

}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
