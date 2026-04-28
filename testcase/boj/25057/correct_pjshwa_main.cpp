#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  string S, T;
  cin >> S >> T;
  int n = S.size(), m = T.size();

  string ns = "", nt = "";
  int sbc = 0, tbc = 0;
  for (int i = 0; i < n; i++) {
    if (S[i] == 'B') sbc++;
    else ns.push_back(S[i]);

    if (ns.size() >= 2 && ns[ns.size() - 1] == ns[ns.size() - 2]) {
      ns.pop_back();
      ns.pop_back();
    }
  }
  for (int i = 0; i < m; i++) {
    if (T[i] == 'B') tbc++;
    else nt.push_back(T[i]);

    if (nt.size() >= 2 && nt[nt.size() - 1] == nt[nt.size() - 2]) {
      nt.pop_back();
      nt.pop_back();
    }
  }

  sbc %= 2;
  tbc %= 2;
  if (sbc == tbc && ns == nt) cout << "YES\n";
  else cout << "NO\n";
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
