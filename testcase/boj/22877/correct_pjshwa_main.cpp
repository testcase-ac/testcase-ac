#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

bool wins(int lc1, int lc2) {
  if (lc1 == 'S' - 'A' && lc2 == 'P' - 'A') return true;
  if (lc1 == 'P' - 'A' && lc2 == 'R' - 'A') return true;
  if (lc1 == 'R' - 'A' && lc2 == 'S' - 'A') return true;
  return false;
}

string S;
int T;
void solve(int l, int r, int lc1, int lc2) {
  if (wins(lc2, lc1)) swap(lc1, lc2);

  string R = string(r - l + 1, ' ');
  int k = 0;

  for (int i = l; i <= r; i++) {
    if (S[i] - 'A' != lc2) continue;

    R[max(i - l - T, k)] = S[i];
    k++;
  }
  for (int i = 0; i < r - l + 1; i++) {
    if (R[i] == ' ') R[i] = 'A' + lc1;
  }
  for (int i = l; i <= r; i++) S[i] = R[i - l];
}

void solve() {
  int N;
  cin >> N >> T >> S;

  int last = 0, lc1 = -1, lc2 = -1;
  for (int i = 0; i < N; i++) {
    int cc = S[i] - 'A';
    if (cc == lc1 || cc == lc2) continue;
    if (lc1 == -1) lc1 = cc;
    else if (lc2 == -1) lc2 = cc;
    else {
      solve(last, i - 1, lc1, lc2);
      last = i;
      lc1 = cc;
      lc2 = -1;
    }
  }
  if (lc2 != -1) solve(last, N - 1, lc1, lc2);

  cout << S << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
