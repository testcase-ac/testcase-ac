#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 20000, MOD = 1e9 + 7;
const ll INF = 1e18;
ll X[MAX + 1], S[MAX + 1];

ll lcm(ll a, ll b) {
  return a / __gcd(a, b) * b;
}

void solve() {
  int N, M;
  cin >> N >> M;
  for (int i = 1; i <= N; i++) cin >> X[i];

  ll ans, di = INF;
  memset(S, -1, sizeof(S));
  for (int i = 1; i <= N; i++) {
    for (int j = 0; j < M; j++) {
      if ((N * j + i) % M == 0) {
        S[i] = j;
        break;
      }
    }

    if (S[i] == -1) {
      ll udays = (X[i] - 1) * N + i;
      if (udays < di) {
        di = udays;
        ans = i;
      }
    }
    else {
      ll left = 1, right = INF;
      ll l = lcm(N, M);
      while (left < right) {
        ll mid = (left + right) / 2;
        ll sdays = (mid - 1) / l;
        if ((mid - 1) % l >= (N * S[i] + i - 1) % l) sdays++;

        ll udays = mid / N;
        if (mid % N >= i) udays++;

        if (udays - sdays >= X[i]) right = mid;
        else left = mid + 1;
      }

      if (di > left) {
        di = left;
        ans = i;
      }
    }

  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
