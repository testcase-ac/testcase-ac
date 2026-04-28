#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  string S; cin >> S;
  int yc = 0, kc = 0;
  for (char c : S) {
    if (yc == 0 && c == 'Y') yc++;
    else if (yc == 1 && c == 'O') yc++;
    else if (yc == 2 && c == 'N') yc++;
    else if (yc == 3 && c == 'S') yc++;
    else if (yc == 4 && c == 'E') yc++;
    else if (yc == 5 && c == 'I') yc++;

    if (kc == 0 && c == 'K') kc++;
    else if (kc == 1 && c == 'O') kc++;
    else if (kc == 2 && c == 'R') kc++;
    else if (kc == 3 && c == 'E') kc++;
    else if (kc == 4 && c == 'A') kc++;
    
    if (yc == 6) return cout << "YONSEI\n", void();
    if (kc == 5) return cout << "KOREA\n", void();
  }
}

int main() {
  // fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
