#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

char suits[4] = {'D', 'C', 'H', 'S'};
char ranks[13] = {'2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'};

bool card_cmp(string &a, string &b) {
  if (a[0] == b[0]) {
    int ai, bi;
    for (int i = 0; i < 4; ++i) {
      if (a[1] == suits[i]) ai = i;
      if (b[1] == suits[i]) bi = i;
    }
    return ai > bi;
  } else {
    int ai, bi;
    for (int i = 0; i < 13; ++i) {
      if (a[0] == ranks[i]) ai = i;
      if (b[0] == ranks[i]) bi = i;
    }
    return ai > bi;
  }
}

void solve() {
  vector<string> P;
  for (int i = 0; i < 26; ++i) {
    string x; cin >> x;
    P.push_back(x);
  }

  vector<string> Q;
  for (int r = 0; r < 4; ++r) for (int s = 0; s < 13; ++s) {
    string x = string(1, ranks[s]) + string(1, suits[r]);
    if (P.end() == find(P.begin(), P.end(), x)) Q.push_back(x);
  }

  sort(P.begin(), P.end(), card_cmp);
  sort(Q.begin(), Q.end(), card_cmp);

  int ans = 0, j = 0;
  for (int i = 0; i < 26; ++i) {
    while (j < 26 && card_cmp(Q[j], P[i])) ++j;
    if (j == 26) break;
    ++ans; ++j;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
