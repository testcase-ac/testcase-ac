#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int main() {
  fast_io();

  int v0, m, t;
  cin >> v0 >> m >> t;

  unordered_map<int, int> u;
  int v = v0, nxt, fv;
  int intv, gap;
  for (int i = 1; i <= 10; i++) {
    u.insert({v, i});
    nxt = (v * m) % 10;

    if (u.count(nxt)) {
      intv = i - u[nxt] + 1;
      gap = u[nxt] - 1;
      fv = nxt;
      break;
    }
    else v = nxt;
  }

  ll d[4] = {0};
  v = v0;
  for (int i = 0; i < gap; i++) {
    d[i % 4] += v;
    v = (v * m) % 10;
  }

  ll rep;
  for (int i = gap; i < gap + (intv * 4); i++) {
    if (i >= t) continue;

    rep = (t - i - 1) / (intv * 4) + 1;
    d[i % 4] += fv * rep;
    fv = (fv * m) % 10;
  }

  cout << d[1] - d[3] << ' ' << d[0] - d[2] << '\n';
}
