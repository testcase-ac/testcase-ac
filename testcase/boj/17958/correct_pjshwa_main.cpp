#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  string S;
  cin >> S;
  sort(S.begin(), S.end());

  map<int, int> t;
  for (char& c : S) {
    t[c - 'a']++;
  }

  int n = S.size() / 2, maj = -1;
  for (auto& [k, v] : t) {
    if (v >= n) maj = k;
  }

  if (maj == -1) {
    cout << "YES\n";
    for (auto& [k, v] : t) {
      for (int i = 0; i < v; ++i) {
        cout << (char)(k + 'a');
      }
    }
    cout << '\n';
    return;
  }

  if (n == 1) {
    if (t.size() == 1) cout << "NO\n";
    else cout << "YES\n" << S << '\n';
    return;
  }
  if (n == 2) {
    if (t[maj] >= 3) cout << "NO\n";
    else cout << "YES\n" << S << '\n';
    return;
  }

  if (t[maj] >= 2 * n - 1) return cout << "NO\n", void();
  else if (t.size() == 2 && t[maj] == 2 * n - 2) return cout << "NO\n", void();

  cout << "YES\n";
  string res = "";
  for (int i = 0; i < n; i++) res += (char)(maj + 'a');
  for (auto& [k, v] : t) {
    if (k == maj) continue;
    res += (char)(k + 'a');
    v--;
    break;
  }
  for (int i = 0; i < t[maj] - n; i++) res += (char)(maj + 'a');
  for (auto& [k, v] : t) {
    if (k == maj) continue;
    for (int i = 0; i < v; i++) {
      res += (char)(k + 'a');
    }
  }

  // set<string> u;
  // for (int i = 0; i < 2 * n; i++) {
  //   string p;
  //   for (int j = 0; j < n; j++) {
  //     p += res[(i + j) % (2 * n)];
  //   }
  //   u.insert(p);
  // }
  // assert(u.size() == 2 * n);
  cout << res << '\n';

}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
