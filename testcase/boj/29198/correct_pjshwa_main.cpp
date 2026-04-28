#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
 
void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, M, K; cin >> N >> M >> K;

  vector<map<int, int>> V;
  for (int i = 0; i < N; i++) {
    string S; cin >> S;
    map<int, int> m;
    for (char c : S) m[c - 'A']++;
    V.push_back(m);
  }

  sort(V.begin(), V.end(), [](auto& a, auto& b) {
    for (int i = 0; i < 26; i++) {
      if (a[i] != b[i]) return a[i] > b[i];
    }
    return false;
  });

  string ans = "";
  for (int i = 0; i < K; i++) {
    auto m = V[i];
    for (auto [k, v] : m) {
      for (int j = 0; j < v; j++) {
        ans += (char)('A' + k);
      }
    }
  }
  sort(ans.begin(), ans.end());
  cout << ans << '\n';
}

int main() {
  fast_io();
 
  int t = 1;
  // cin >> t;
  while (t--) solve();
}
