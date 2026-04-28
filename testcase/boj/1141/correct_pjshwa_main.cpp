#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 50;

bool starts_with(string a, string b) {
  if (a.size() < b.size()) return false;
  for (int i = 0; i < b.size(); ++i) {
    if (a[i] != b[i]) return false;
  }
  return true;
}

void solve() {
  int N; cin >> N;
  vector<string> A(N);
  for (int i = 0; i < N; i++) cin >> A[i];
  sort(A.begin(), A.end(), greater<string>());

  vector<string> ans;
  for (int i = 0; i < N; i++) {
    bool ok = true;
    for (string& o : ans) {
      if (starts_with(o, A[i])) {
        ok = false;
        break;
      }
    }
    if (ok) ans.push_back(A[i]);
  }
  cout << ans.size() << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
