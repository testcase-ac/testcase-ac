#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1000;
int PL[MAXN + 10], PR[MAXN + 10];

int ask(int l, int r) {
  cout << "? " << l << ' ' << r << endl;
  int ret; cin >> ret;
  return ret;
}

void solve() {
  int N; cin >> N;
  for (int i = 1; i <= N; ++i) {
    PL[i] = ask(1, i);
    PR[i] = ask(i, N);
  }

  vector<int> U;
  for (int i = 1; i <= N; ++i) {
    if (PL[i] != PL[i - 1] + 1) continue;
    if (PR[i] != PR[i + 1] + 1) continue;
    U.push_back(i);
  }

  cout << "! " << U.size();
  for (int e : U) cout << ' ' << e;
  cout << endl;
}

int main() {
  // fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
