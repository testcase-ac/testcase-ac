#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
int a[5][4];

ll cal(ll s1, ll s2, ll m1, ll m2, ll dur) {
  ll val = 0;

  if (m1 == 0) {
    if (m2 == 0) {
      val += dur * (dur - 1) * (2 * dur - 1) / 6;
      val += (s1 + s2) * dur * (dur - 1) / 2;
      val += s1 * s2 * dur;
    }
    if (m2 == 1) {
      val += s2 * dur * (dur - 1) / 2;
      val += s1 * s2 * dur;
    }
    if (m2 == 2) {
      val -= dur * (dur - 1) * (2 * dur - 1) / 6;
      val += (s2 - s1) * dur * (dur - 1) / 2;
      val += s1 * s2 * dur;
    }
  }
  if (m1 == 1) {
    if (m2 == 0) {
      val += s1 * dur * (dur - 1) / 2;
      val += s1 * s2 * dur;
    }
    if (m2 == 1) {
      val += s1 * s2 * dur;
    }
    if (m2 == 2) {
      val -= s1 * dur * (dur - 1) / 2;
      val += s1 * s2 * dur;
    }
  }
  if (m1 == 2) {
    if (m2 == 0) {
      val -= dur * (dur - 1) * (2 * dur - 1) / 6;
      val += (s1 - s2) * dur * (dur - 1) / 2;
      val += s1 * s2 * dur;
    }
    if (m2 == 1) {
      val -= s2 * dur * (dur - 1) / 2;
      val += s1 * s2 * dur;
    }
    if (m2 == 2) {
      val += dur * (dur - 1) * (2 * dur - 1) / 6;
      val -= (s1 + s2) * dur * (dur - 1) / 2;
      val += s1 * s2 * dur;
    }
  }
  return val;
}

void solve() {
  for (int i = 1; i <= 4; i++) for (int j = 0; j < 4; j++) cin >> a[i][j];

  int outer[4] = {
    max(a[2][2], a[3][2]),
    max(a[3][3], a[4][3]),
    min(a[1][2], a[4][2]),
    min(a[1][3], a[2][3])    
  };
  int inner[4] = {
    min(a[2][0], a[3][0]),
    min(a[3][1], a[4][1]),
    max(a[1][0], a[4][0]),
    max(a[1][1], a[2][1])
  };

  if (inner[0] < outer[0]) return cout << "0\n", void();
  if (inner[1] < outer[1]) return cout << "0\n", void();
  if (inner[2] > outer[2]) return cout << "0\n", void();
  if (inner[3] > outer[3]) return cout << "0\n", void();

  vector<pii> cps;
  cps.push_back({inner[3] - outer[2] - 1, 1});
  cps.push_back({outer[3] - outer[2], 1});
  cps.push_back({inner[3] - inner[2], 1});
  cps.push_back({outer[3] - inner[2] + 1, 1});

  cps.push_back({outer[1] - inner[0] - 1, 2});
  cps.push_back({inner[1] - inner[0], 2});
  cps.push_back({outer[1] - outer[0], 2});
  cps.push_back({inner[1] - outer[0] + 1, 2});

  sort(cps.begin(), cps.end());

  ll ans = 0;
  int s1 = 0, s2 = 0, m1 = -1, m2 = -1, lastk = -1;
  for (auto [k, s] : cps) {
    int dur = k - lastk;
    ans += cal(s1, s2, m1, m2, dur);

    if (m1 == 0) s1 += dur;
    if (m2 == 0) s2 += dur;

    if (m1 == 2) s1 -= dur;
    if (m2 == 2) s2 -= dur;

    if (s == 1) m1++;
    if (s == 2) m2++;

    lastk = k;
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
