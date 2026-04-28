#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 2e5, MOD = 1e9 + 7;
int A[MAX + 1];

void solve() {
  int N, s;
  cin >> N >> s;
  for (int i = 1; i <= N; i++) cin >> A[i];

  deque<ll> L, R;
  for (int i = 1; i < s; i++) {
    if (A[i] == 0) continue;

    if (L.empty()) {
      if (A[i] < 0) continue;
      else L.push_back(A[i]);
    }
    else {
      bool sign1 = L.back() > 0, sign2 = A[i] > 0;
      if (sign1 == sign2) {
        ll pre = L.back(); L.pop_back();
        L.push_back(pre + A[i]);
      }
      else L.push_back(A[i]);
    }
  }
  for (int i = N; i > s; i--) {
    if (A[i] == 0) continue;

    if (R.empty()) {
      if (A[i] < 0) continue;
      else R.push_back(A[i]);
    }
    else {
      bool sign1 = R.back() > 0, sign2 = A[i] > 0;
      if (sign1 == sign2) {
        ll pre = R.back(); R.pop_back();
        R.push_back(pre + A[i]);
      }
      else R.push_back(A[i]);
    }
  }

  ll ans = 0;
  if (!L.empty() && L.back() > 0) ans += L.back(), L.pop_back();
  if (!R.empty() && R.back() > 0) ans += R.back(), R.pop_back();

  deque<pll> dL, dR;
  assert(L.size() % 2 == 0); assert(R.size() % 2 == 0);

  while (!L.empty()) {
    ll neg = L.back(); L.pop_back();
    ll pos = L.back(); L.pop_back();

    ll net = pos + neg;
    if (dL.empty()) dL.push_back({neg, net});
    else {
      auto [pneg, pnet] = dL.back();
      if (pnet > 0) dL.push_back({neg, net});
      else {
        dL.pop_back();
        dL.push_back({min(pneg, neg + pnet), pnet + net});
      }
    }
  }
  while (!R.empty()) {
    ll neg = R.back(); R.pop_back();
    ll pos = R.back(); R.pop_back();

    ll net = pos + neg;
    if (dR.empty()) dR.push_back({neg, net});
    else {
      auto [pneg, pnet] = dR.back();
      if (pnet > 0) dR.push_back({neg, net});
      else {
        dR.pop_back();
        dR.push_back({min(pneg, neg + pnet), pnet + net});
      }
    }
  }

  while (1) {
    ll gain = 0;

    if (dL.size()) {
      auto [lneg, lnet] = dL.front();
      if (lnet > 0 && ans + lneg >= 0) dL.pop_front(), gain += lnet;
    }

    if (dR.size()) {
      auto [rneg, rnet] = dR.front();
      if (rnet > 0 && ans + rneg >= 0) dR.pop_front(), gain += rnet;
    }

    if (gain == 0) break;
    ans += gain;
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
