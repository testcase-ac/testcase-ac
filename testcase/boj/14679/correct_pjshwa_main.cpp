#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const ll MAXN = 1e5, MOD = 1e9 + 7;
const ll MAXA = 100, MAXD = 3, MAXH = 1000;

ll lpow(ll x, ll y, ll m) {
  ll r = 1;
  x %= m;
  while (y) {
    if (y & 1) r = (r * x) % m;
    x = (x * x) % m;
    y >>= 1;
  }
  return r;
}

bool f(int h) {
  int a = 1, d = 1, ma = MAXA, md = MAXD, mh = MAXH;
  while (1) {
    mh -= max(1, a - md);
    if (mh <= 0) return true;
    h -= max(1, ma - d);
    if (h <= 0) return false;
  }
  return false;
}

void solve() {
  // Can't lose after monster 98902
  // for (int h = 1;; ++h) {
  //   if (f(h)) return cout << h << '\n', void();
  // }

  ll N, A, D, H, MA, MD, MH; cin >> N >> A >> D >> H >> MA >> MD >> MH;
  ll Ap, Aa, Dp, Da, Hp, Ha; cin >> Ap >> Aa >> Dp >> Da >> Hp >> Ha;
  ll CMA = MA, CMD = MD, CMH = MH;
  for (int t = 1; t <= min(N, MAXN); ++t) {
    ll a = A, d = D, h = H, ma = CMA, md = CMD, mh = CMH;
    while (1) {
      mh -= max(1LL, a - md);
      if (mh <= 0) break;
      h -= max(1LL, ma - d);
      if (h <= 0) return cout << "-1\n", void();
    }
    A += CMA, D += CMD, H += CMH;
    CMA = (lpow(CMA, Ap, MAXA) + Aa) % MAXA + 1;
    CMD = (lpow(CMD, Dp, MAXD) + Da) % MAXD + 1;
    CMH = (lpow(CMH, Hp, MAXH) + Ha) % MAXH + 1;
  }

  if (N <= MAXN) {
    cout << A << ' ' << D << ' ' << H << '\n';
    return;
  }

  // at this point we know player won't lose
  // calculate cycle sum and length for MA, MD, MH
  ll sumMA = 0, sumMD = 0, sumMH = 0, lenMA = 0, lenMD = 0, lenMH = 0;
  {
    int x = CMA;
    do {
      sumMA += x;
      x = (lpow(x, Ap, MAXA) + Aa) % MAXA + 1;
      ++lenMA;
    } while (x != CMA);
  }
  {
    int x = CMD;
    do {
      sumMD += x;
      x = (lpow(x, Dp, MAXD) + Da) % MAXD + 1;
      ++lenMD;
    } while (x != CMD);
  }
  {
    int x = CMH;
    do {
      sumMH += x;
      x = (lpow(x, Hp, MAXH) + Ha) % MAXH + 1;
      ++lenMH;
    } while (x != CMH);
  }

  ll tMA = (N - MAXN) / lenMA, rMA = (N - MAXN) % lenMA;
  A = (A + tMA * sumMA % MOD) % MOD;
  {
    int x = CMA;
    for (int i = 0; i < rMA; ++i) {
      A = (A + x) % MOD;
      x = (lpow(x, Ap, MAXA) + Aa) % MAXA + 1;
    }
  }
  ll tMD = (N - MAXN) / lenMD, rMD = (N - MAXN) % lenMD;
  D = (D + tMD * sumMD % MOD) % MOD;
  {
    int x = CMD;
    for (int i = 0; i < rMD; ++i) {
      D = (D + x) % MOD;
      x = (lpow(x, Dp, MAXD) + Da) % MAXD + 1;
    }
  }
  ll tMH = (N - MAXN) / lenMH, rMH = (N - MAXN) % lenMH;
  H = (H + tMH * sumMH % MOD) % MOD;
  {
    int x = CMH;
    for (int i = 0; i < rMH; ++i) {
      H = (H + x) % MOD;
      x = (lpow(x, Hp, MAXH) + Ha) % MAXH + 1;
    }
  }

  cout << A << ' ' << D << ' ' << H << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
