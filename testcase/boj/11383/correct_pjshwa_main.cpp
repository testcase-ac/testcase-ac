#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int N, M;
  cin >> N >> M;

  bool eyfa = true;
  string S[N], T[N];
  for (int i = 0; i < N; i++) cin >> S[i];
  for (int i = 0; i < N; i++) cin >> T[i];

  for (int i = 0; i < N; i++) {
    string ns = "";
    for (char& c : S[i]) {
      ns += c;
      ns += c;
    }

    eyfa &= (ns == T[i]);
  }

  if (eyfa) cout << "Eyfa\n";
  else cout << "Not Eyfa\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
