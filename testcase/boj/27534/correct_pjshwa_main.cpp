#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; string S; cin >> N >> S;
  if (N == 1 || N == 3) return cout << "-1\n", void();

  int omin = N, omax = -1, zmin = N, zmax = -1;
  for (int i = 0; i < N; i++) {
    if (S[i] == '0') zmin = min(zmin, i), zmax = max(zmax, i);
    else omin = min(omin, i), omax = max(omax, i);
  }
  if (omax - omin == zmax - zmin) return cout << "0\n", void();

  int zprv[N], znxt[N], oprv[N], onxt[N], olast, zlast;

  olast = zlast = -1;
  for (int i = 0; i < N; i++) {
    zprv[i] = zlast; oprv[i] = olast;
    if (S[i] == '0') zlast = i;
    else olast = i;
  }
  olast = zlast = -1;
  for (int i = N - 1; i >= 0; i--) {
    znxt[i] = zlast; onxt[i] = olast;
    if (S[i] == '0') zlast = i;
    else olast = i;
  }

  for (int i = 0; i < N; i++) {
    int czmin = zmin, czmax = zmax, comin = omin, comax = omax;
    if (S[i] == '0') {
      comin = min(comin, i), comax = max(comax, i);
      if (i == zmax) czmax = zprv[i];
      if (i == zmin) czmin = znxt[i];
      if (czmin == -1 || czmax == -1) continue;

      if (czmax - czmin == comax - comin) return cout << "1\n", void();
    }
    else {
      czmin = min(czmin, i), czmax = max(czmax, i);
      if (i == omax) comax = oprv[i];
      if (i == omin) comin = onxt[i];
      if (comin == -1 || comax == -1) continue;

      if (czmax - czmin == comax - comin) return cout << "1\n", void();
    }
  }

  cout << "2\n";
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
