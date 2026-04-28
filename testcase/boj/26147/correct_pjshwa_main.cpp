#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N;

  string R = "ABCDE";
  vector<string> Q;
  for (int i = 0; i < N; i++) {
    string S; cin >> S;
    string T = "ZZZZZ";

    int yc = 0, gc = 0; vector<int> ys;
    for (int j = 0; j < 5; j++) {
      if (S[j] == 'Y') {
        yc++; ys.push_back(j);
      }
      if (S[j] == 'G') {
        gc++;
        T[j] = R[j];
      }
    }
    if (gc == 4 && yc == 1) return cout << "IMPOSSIBLE\n", void();

    if (yc == 1) {
      for (int j = 0; j < 5; j++) {
        if (S[j] != 'G' && j != ys[0]) {
          T[ys[0]] = R[j];
          break;
        }
      }
    }
    else if (yc > 1) {
      for (int j = 0; j < yc; j++) {
        int nj = ys[(j + 1) % yc];
        T[ys[j]] = R[nj];
      }
    }

    Q.push_back(T);
  }

  cout << R << '\n';
  for (auto& s : Q) cout << s << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
