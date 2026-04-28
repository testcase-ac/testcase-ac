#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

bool is_preceding(string& a, string& b) {
  int z = min(a.size(), b.size());
  for (int i = 0; i < z; ++i) {
    if (a[i] > b[i]) return false;
    if (a[i] < b[i]) return true;
  }
  return a.size() < b.size();
}

bool starts_with(string& a, string& b) {
  if (a.size() > b.size()) return false;

  int z = a.size();
  for (int i = 0; i < z; ++i) {
    if (a[i] != b[i]) return false;
  }
  return true;
}

bool is_special(string& s) {
  int z = s.size();
  for (int i = 1; i < z; ++i) {
    string U = s.substr(0, i);
    string V = s.substr(i, z - i);
    if (!is_preceding(U, V)) return false;
  }
  return true;
}

int N, maxz;
string S, cur;

void dfs(int i) {
  if (i == N && cur != S) {
    cout << cur << '\n';
    exit(0);
  }

  int l = N - i, z = min(l, maxz);
  for (int zc = maxz; zc >= 0; --zc) for (int oc = 0; oc <= l; ++oc) {
    if (zc + oc > l) break;

    for (int j = 0; j < zc; ++j) cur.push_back('0');
    for (int j = 0; j < oc; ++j) cur.push_back('1');

    cout << "S = " << S << ", cur = " << cur << ", is_preceding = " << is_preceding(S, cur) << '\n';
    if (!is_preceding(cur, S) && zc + oc > 0) {
      dfs(i + zc + oc);
    }
    for (int j = 0; j < zc; ++j) cur.pop_back();
    for (int j = 0; j < oc; ++j) cur.pop_back();
  }
}

void solve() {
  cin >> S;
  N = S.size();

  for (int i = 0; i < N; ++i) {
    if (S[i] == '0') ++maxz;
    else break;
  }
  dfs(0);
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
