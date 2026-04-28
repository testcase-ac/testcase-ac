#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

ll pw[19];

void solve() {
  string s1, s2, s3;
  cin >> s1 >> s2 >> s3;

  set<char> u;
  for (char c : s1) u.insert(c);
  for (char c : s2) u.insert(c);
  for (char c : s3) u.insert(c);
  if (u.size() > 10) return cout << "NO\n", void();

  int p[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}, n = u.size();
  reverse(s1.begin(), s1.end());
  reverse(s2.begin(), s2.end());
  reverse(s3.begin(), s3.end());

  vector<char> cv = {u.begin(), u.end()};
  ll c1[128], c2[128];
  memset(c1, 0, sizeof(c1));
  memset(c2, 0, sizeof(c2));
  for (int vi = 0; vi < n; vi++) {
    char c = cv[vi];
    for (int i = 0; i < s1.size(); i++) if (s1[i] == c) c1[(int)c] += pw[i];
    for (int i = 0; i < s2.size(); i++) if (s2[i] == c) c1[(int)c] += pw[i];
    for (int i = 0; i < s3.size(); i++) if (s3[i] == c) c2[(int)c] += pw[i];
  }

  do {
    ll lhs = 0, rhs = 0;
    for (int vi = 0; vi < n; vi++) {
      char c = cv[vi];
      lhs += c1[(int)c] * p[vi];
      rhs += c2[(int)c] * p[vi];
    }
    if (lhs == rhs) {
      // for (int vi = 0; vi < n; vi++) {
      //   cout << cv[vi] << ": " << p[vi] << endl;
      // }
      return cout << "YES\n", void();
    }

  } while (next_permutation(p, p + 10));

  cout << "NO\n";
}

int main() {
  fast_io();

  pw[0] = 1;
  for (int i = 1; i <= 18; i++) pw[i] = pw[i - 1] * 10;

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
