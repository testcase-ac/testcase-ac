#include <bits/stdc++.h>
typedef long long ll;
#define pii pair<int, int>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int main() {
  fast_io();

  int n, m, s, d, cx, ix = 0;
  double sq;
  cin >> n >> m;

  map<int, int> cpx;
  map<int, vector<pii>> dt;
  for (int i = 0; i < n; i++) {
    cin >> s;

    if (dt.count(i)) {
      for (auto[el, cnt] : dt[i]) cpx[el] += cnt;
    }

    if (s % 7 != 0 || s % 49 == 0) {
      cout << "-1\n";
      return 0;
    }
    s /= 7;

    cx = 0;
    while (s % 2 == 0) {
      cx++;
      s /= 2;
    }
    if (cx > 0) {
      if (!cpx.count(2)) cpx[2] = 0;
      d = cx - cpx[2];
      if (d > 0) {
        ix += d;
        cpx[2] = cx;
        if (!dt.count(i + m)) {
          vector<pii> v;
          dt[i + m] = v;
        }
        dt[i + m].push_back({2, -d});
      }
    }

    sq = sqrt(s);
    for (int k = 3; k <= sq; k = k + 2) {
      cx = 0;
      while (s % k == 0) {
        cx++;
        s /= k;
      }

      if (cx > 0) {
        if (!cpx.count(k)) cpx[k] = 0;
        d = cx - cpx[k];
        if (d > 0) {
          ix += d;
          cpx[k] = cx;
          if (!dt.count(i + m)) {
            vector<pii> v;
            dt[i + m] = v;
          }
          dt[i + m].push_back({k, -d});
        }
      }
    }

    if (s > 2) {
      if (!cpx.count(s)) cpx[s] = 0;
      d = 1 - cpx[s];
      if (d > 0) {
        ix += d;
        cpx[s] = 1;
        if (!dt.count(i + m)) {
          vector<pii> v;
          dt[i + m] = v;
        }
        dt[i + m].push_back({s, -d});
      }
    }
  }

  cout << ix << '\n';
}
