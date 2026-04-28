#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  string S;
  map<string, vector<string>> m;
  while (cin >> S) {
    string key = S;
    sort(key.begin(), key.end());
    m[key].push_back(S);
  }

  vector<vector<string>> U;
  for (auto& [_, v] : m) {
    sort(v.begin(), v.end());
    U.push_back(v);
  }

  sort(U.begin(), U.end(), [](const auto& a, const auto& b) {
    int az = a.size(), bz = b.size();
    if (az != bz) return az > bz;
    else return a[0] < b[0];
  });

  int Z = min(5, (int)U.size());
  for (int i = 0; i < Z; ++i) {
    cout << "Group of size " << U[i].size() << ": ";

    set<string> S;
    for (auto& s : U[i]) S.insert(s);
    for (auto& s : S) cout << s << ' ';
    cout << ".\n";
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
