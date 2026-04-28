#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  ll N, M, K, A, B, C, T; cin >> N >> M >> K >> A >> B >> C >> T;

  vector<int> U(M);
  for (int i = 0; i < M; i++) cin >> U[i], U[i]--;
  K -= M;

  ll S, ans = 0;
  priority_queue<ll> rest;
  for (int i = 0; i < M - 1; i++) {
    S = B * U[i];
    if (S > T) break;
    ans++;

    ll pos = U[i];
    ll dif = U[i + 1] - pos - 1, nxt = (T - S) / A;

    if (nxt >= dif) {
      ans += dif;
      continue;
    }

    pos += nxt + 1;
    S += C * (nxt + 1);
    ans += nxt;

    int trial = K;
    while (trial-- && pos < U[i + 1] && S <= T) {
      dif = U[i + 1] - pos - 1, nxt = (T - S) / A;
      if (nxt >= dif) {
        rest.push(dif + 1);
        break;
      }
      else {
        pos += nxt + 1;
        S += C * (nxt + 1);
        rest.push(nxt + 1);
      }
    }
  }

  while (K-- && rest.size()) {
    ans += rest.top(); rest.pop();
  }
  if (B * (N - 1) <= T) ans++;
  cout << ans - 1 << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
