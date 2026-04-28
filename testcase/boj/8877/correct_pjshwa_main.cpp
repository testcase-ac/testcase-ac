#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

int s2i(string S) {
  if (S == "00") return -1;
  int b = S[0] - 'A';
  if (S[1] == '+') b += 26;
  return b;
}

const int INF = 0x3f3f3f3f;
int cdist[52][52];

void solve() {
  int N; cin >> N;

  memset(cdist, 0x3f, sizeof(cdist));
  for (int i = 0; i < N; ++i) {
    string S; cin >> S;
    int a = s2i(S.substr(0, 2)), b = s2i(S.substr(2, 2));
    int c = s2i(S.substr(4, 2)), d = s2i(S.substr(6, 2));

    vector<int> V = {a, b, c, d};
    for (int i = 0; i < 4; ++i) for (int j = 0; j < 4; ++j) {
      int u = V[i], v = V[j];
      if (u == -1 || v == -1 || i == j) continue;
      cdist[u][(v >= 26 ? v - 26 : v + 26)] = 1;
    }
  }

  // check if graph contains cycle
  for (int k = 0; k < 52; ++k) for (int i = 0; i < 52; ++i) for (int j = 0; j < 52; ++j) {
    cdist[i][j] = min(cdist[i][j], cdist[i][k] + cdist[k][j]);
  }

  for (int i = 0; i < 52; ++i) if (cdist[i][i] != INF) {
    cout << "unbounded\n";
    return;
  }
  cout << "bounded\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
