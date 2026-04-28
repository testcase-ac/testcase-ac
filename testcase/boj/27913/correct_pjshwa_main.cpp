#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

bool is_upper(char c) {
  return 'A' <= c && c <= 'Z';
}

void solve() {
  int N, Q; cin >> N >> Q;

  string S = "SciComLove", R = "";
  for (int i = 0; i < N; i++) R += S[i % 10];

  int ucnt = 0;
  for (int i = 0; i < N; i++) {
    if (is_upper(R[i])) ucnt++;
  }

  while (Q--) {
    int x; cin >> x;
    if (is_upper(R[x - 1])) {
      ucnt--;
      R[x - 1] = tolower(R[x - 1]);
    }
    else {
      ucnt++;
      R[x - 1] = toupper(R[x - 1]);
    }
    cout << ucnt << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
