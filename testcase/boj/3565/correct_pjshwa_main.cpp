#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

// N자리까지 적었을 때 일단 마지막에 적힌 수 (혹은 적히다 만 수) 가 얼마인지를 포착해야
// 해당 수를 k라고 하자. k의 1의 개수 (N자리까지) 우선 세주고, f(k - 1)을 호출.

// f(n)은 만약 n이 d자리라면, d-1자리까지의 1의 개수를 모두 센 뒤 d자리의 자신까지의 개수를 센 뒤
// n이 d자리의 i번째 수라면 f(i - 1)을 호출하고, 그 값을 더해서 반환한다.

// i자리 수의 1의 개수 합을 빨리 구할 수 있도록 미리 계산해둔다.

// n자리 수의 개수는 그냥 F(n - 1)이다.
// n자리 수의 1의 개수를 G(n) 이라 하면 G(n) = F(n - 1) + G(n - 2) + G(n - 3) + G(n - 4) + ...

ll F[80], G[80];
ll f(ll n) {
  if (n == 0) return 0;

  ll C = 0, ret = 0;
  for (int i = 1;; i++) {
    // n has i digits
    if (C + F[i - 1] >= n) {
      for (int j = i - 1; j >= 0; j--) ret += G[j];

      ll r = n - C;
      return ret + r + f(r - 1);
    }
    C += F[i - 1];
  }

  // You should never reach here.
  return -1;
}

void solve() {
  ll N;
  cin >> N;
  if (N == 0) return cout << "0\n", void();

  ll C = 0, ans = 0;
  for (int i = 1;; i++) {
    // k has i digits
    if (C + F[i - 1] * i >= N) {
      for (int j = i - 1; j >= 0; j--) {
        if (j) N -= F[j - 1] * j;
      }

      // k is rth number of i digits
      ll r = (N - 1) / i + 1;
      ll k = F[i] - 1 + r;

      ll d = i, ok = k;
      string ks = "";
      while (d >= 1) {
        if (ok >= F[d]) {
          ok -= F[d];
          if (d == 1) {
            d--;
            ks += '1';
          }
          else {
            d -= 2;
            ks += "10";
          }
        }
        else {
          d--;
          ks += '0';
        }
      }

      for (int j = 0; j <= (N - 1) % i; j++) {
        if (ks[j] == '1') ans++;
      }
      ans += f(k - 1);

      break;
    }
    C += F[i - 1] * i;
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  F[0] = F[1] = 1; F[2] = 2;
  G[0] = 0; G[1] = G[2] = 1;
  for (int i = 3; i < 80; i++) {
    F[i] = F[i - 1] + F[i - 2];
    G[i] = F[i - 1];
    for (int j = i - 2; j >= 0; j--) G[i] += G[j];
  }

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
 