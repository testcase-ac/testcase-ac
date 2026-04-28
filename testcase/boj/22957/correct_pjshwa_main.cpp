#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

ll ec[31] = {0, 3, 9, 36, 96, 339, 885, 3072, 7992, 27675, 71961, 249108, 647688, 2242011, 5829237, 20178144, 52463184, 181603347, 472168713, 1634430180, 4249518480, 14709871683, 38245666389, 132388845216, 344210997576, 1191499607019, 3097898978265, 10723496463252, 27881090804472, 96511468169355, 250929817240341};
string ans = "";

int xclu(int a, int b) {
  if (a == b) return 0;
  if (a == 3 && b == 5) return 7;
  if (a == 3 && b == 7) return 5;
  if (a == 5 && b == 3) return 7;
  if (a == 5 && b == 7) return 3;
  if (a == 7 && b == 3) return 5;
  if (a == 7 && b == 5) return 3;
}

void track_even(int n, ll k, int num) {
  if (n == 0) return;

  if (num == 0) {
    if (n & 1) {
      ll df = (ec[n + 1] - ec[n]) / 3;
      ll ck = k - ec[n];
      ll cdf = df / 3, cx = 0;
      for (int j : {3, 5, 7}) {
        cx += (cdf + 1);
        if (ck <= cx) {
          ans += to_string(j), track_even(n - 1, k - cx - (ec[n] - ec[n - 1]), j);
          break;
        }
      }
    }
    else {
      ll ck = k - ec[n - 1], df = (ec[n] - ec[n - 1]) / 3;
      if (ck <= df) ans += '3', track_even(n - 1, k, 3);
      else if (ck <= 2 * df) ans += '5', track_even(n - 1, k - df, 5);
      else ans += '7', track_even(n - 1, k - 2 * df, 7);
    }
  }
  else {
    if (n & 1) {
      ll df = (ec[n + 1] - ec[n]) / 3;
      ll ck = k - ec[n], cdf = df / 3, cx = 0;
      for (int j : {3, 5, 7}) {
        cx += (num == j ? cdf : cdf + 1);
        if (ck <= cx) {
          ans += to_string(j), track_even(n - 1, k - cx - (ec[n] - ec[n - 1]), xclu(num, j));
          break;
        }
      }
    }
    else {
      k++;
      ll ck = k - ec[n - 1], df = (ec[n] - ec[n - 1]) / 3;
      ll cx = 0, ncx = 0;
      for (int j : {3, 5, 7}) {
        ncx += (num == j ? df + 1 : df);
        if (ck <= ncx) {
          ans += to_string(j), track_even(n - 1, k - cx, xclu(num, j));
          break;
        }
        cx = ncx;
      }
    }
  }
}

int main() {
  fast_io();

  ll n, k;
  cin >> n >> k;
  k = ec[n] - k + 1;

  int ni = 0;
  while (ec[ni] < k) ni++;

  if (ni & 1) {
    ll df = (ec[ni] - ec[ni - 1]) / 3;
    k -= ec[ni - 1];

    while (1) {
      if (k <= df) ans += '3';
      else if (k <= 2 * df) ans += '5';
      else ans += '7';

      k = (k - 1) % df + 1;
      df /= 3;
      if (!df) break;
    }
  }
  else track_even(ni, k, 0);

  cout << ans;
}
