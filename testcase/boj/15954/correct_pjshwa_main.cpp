#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

ll pf[501], pf_sq[501];

ld sd_of_segment(int l, int r) {
  ll s = pf[r], s_sq = pf_sq[r];
  if (l) {
    s -= pf[l - 1];
    s_sq -= pf_sq[l - 1];
  }
  ld m = s, m_sq = s_sq;
  m /= (r - l + 1);
  m_sq /= (r - l + 1);

  return sqrt(m_sq - m * m);
}

int main() {
  fast_io();

  int n, k;
  cin >> n >> k;
  for (int i = 0; i < n; i++) {
    cin >> pf[i];
    pf_sq[i] = pf[i] * pf[i];
    if (i > 0) {
      pf[i] += pf[i - 1];
      pf_sq[i] += pf_sq[i - 1];
    }
  }

  ld mv = 1e18;
  for (int i = 0; i < n; i++) for (int ki = k; i + ki <= n; ki++) mv = min(mv, sd_of_segment(i, i + ki - 1));
  cout << fixed << setprecision(12) << mv;
}
