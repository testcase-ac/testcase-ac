#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1000;
string S, T;
bool ds[MAX + 1][MAX + 1], dt[MAX + 1][MAX + 1];
bool ps[MAX + 1];

void solve() {
  int ssz = S.size(), tsz = T.size();

  for (int i = 0; i < ssz; i++) ds[i][i] = true;
  for (int i = 0; i < ssz - 1; i++) ds[i][i + 1] = S[i] == S[i + 1];
  for (int diff = 2; diff < ssz; diff++) {
    for (int i = 0; i < ssz - diff; i++) {
      int j = i + diff;
      ds[i][j] = (S[i] == S[j] && ds[i + 1][j - 1]);
    }
  }

  for (int i = 0; i < tsz; i++) dt[i][i] = true;
  for (int i = 0; i < tsz - 1; i++) dt[i][i + 1] = T[i] == T[i + 1];
  for (int diff = 2; diff < tsz; diff++) {
    for (int i = 0; i < tsz - diff; i++) {
      int j = i + diff;
      dt[i][j] = (T[i] == T[j] && dt[i + 1][j - 1]);
    }
  }

  int si = -1, ti = -1;
  for (int i = 0; i <= ssz; i++) {
    if (i < ssz && !ds[i][ssz - 1]) continue;

    bool p = true;
    for (int j = 0; j < (tsz + i) / 2; j++) {
      char lc = j >= tsz ? S[i - 1 - (j - tsz)] : T[j];
      char rc = (tsz + i - 1 - j) >= tsz ? S[i - 1 - (tsz + i - 1 - j - tsz)] : T[tsz + i - 1 - j];

      if (lc != rc) {
        p = false;
        break;
      }
    }

    if (!p) {
      si = i;
      break;
    }
  }

  for (int i = 0; i <= tsz; i++) {
    if (i < tsz && !dt[i][tsz - 1]) continue;

    bool p = true;
    for (int j = 0; j < (ssz + i) / 2; j++) {
      char lc = j >= ssz ? T[i - 1 - (j - ssz)] : S[j];
      char rc = (ssz + i - 1 - j) >= ssz ? T[i - 1 - (ssz + i - 1 - j - ssz)] : S[ssz + i - 1 - j];
      if (lc != rc) {
        p = false;
        break;
      }
    }

    if (!p) {
      ti = i;
      break;
    }
  }

  if (si == -1 && ti == -1) cout << "No Solution.\n";
  else {
    string sans = S.substr(0, si), tans = T.substr(0, ti);
    reverse(sans.begin(), sans.end());
    reverse(tans.begin(), tans.end());

    if (sans.size() < tans.size()) cout << sans << '\n';
    else if (sans.size() > tans.size()) cout << tans << '\n';
    else cout << min(sans, tans) << '\n';
  }
}

int main() {
  fast_io();

  while (1) {
    if (!getline(cin, S)) break;
    if (!getline(cin, T)) break;
    solve();
  }
}
