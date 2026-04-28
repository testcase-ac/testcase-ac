#include <bits/stdc++.h> 
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

ll dig_naive(ll m) {
  int s = 0;
  while (m) {
    s += m % 10;
    m /= 10;
  }
  if (s >= 10) return dig_naive(s);
  return s;
}

void solve() {
  ll k, m;
  cin >> k >> m;

  ll s = 1, q = m * m * m * m;
  int cnt = (k - 1) / 4;
  ll a[4];

  for (int i = 0; i < 4; i++) {
    int st = dig_naive(s);
    map<int, int> c;
    int v[20];
    int gap, gstart;
    for (int j = 0; j < 20; j++) {
      if (c.count(st)) {
        gstart = c[st];
        gap = j - gstart;
        break;
      }
      c[st] = j;
      v[j] = st;
      st = dig_naive(q * st);
    }

    int gsum = 0;
    for (int j = gstart; j < gstart + gap; j++) gsum += v[j];

    int ccnt = cnt;
    if ((k - 1) % 4 >= i) ccnt++;

    ll dist = 0, ss = s;
    for (int j = 0; j < min(gstart, ccnt); j++) {
      ss = dig_naive(ss);
      dist += ss;
      ss *= q;
    }
    ccnt = max(0, ccnt - gstart);
    dist += (ll)(ccnt / gap) * gsum;
    ccnt %= gap;
    for (int j = gstart; j < gstart + ccnt; j++) {
      dist += v[j];
    }
    a[i] = dist;
    s *= m;
  }

  cout << a[1] - a[3] << ' ' << a[0] - a[2] << '\n';
}

int main() {
  fast_io();

  int t;
  cin >> t;
  while (t--) solve();
}
